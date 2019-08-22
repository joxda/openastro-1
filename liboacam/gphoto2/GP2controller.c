/*****************************************************************************
 *
 * GP2controller.c -- Main camera controller thread
 *
 * Copyright 2019
 *   James Fidell (james@openastroproject.org)
 *
 * License:
 *
 * This file is part of the Open Astro Project.
 *
 * The Open Astro Project is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * The Open Astro Project is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with the Open Astro Project.  If not, see
 * <http://www.gnu.org/licenses/>.
 *
 *****************************************************************************/

#include <oa_common.h>

#include <pthread.h>

#include <openastro/camera.h>
#include <openastro/util.h>
#include <sys/time.h>

#include "oacamprivate.h"
#include "unimplemented.h"
#include "GP2oacam.h"
#include "GP2state.h"
#include "GP2private.h"


static int	_processGetControl ( oaCamera*, OA_COMMAND* );
static int	_processSetControl ( oaCamera*, OA_COMMAND* );


void*
oacamGP2controller ( void* param )
{
  oaCamera*		camera = param;
  GP2_STATE*		cameraInfo = camera->_private;
  OA_COMMAND*		command;
  int			exitThread = 0;
  int			resultCode;
  int			streaming = 0;

  do {
    pthread_mutex_lock ( &cameraInfo->commandQueueMutex );
    exitThread = cameraInfo->stopControllerThread;
    pthread_mutex_unlock ( &cameraInfo->commandQueueMutex );
    if ( exitThread ) {
      break;
    } else {
      pthread_mutex_lock ( &cameraInfo->commandQueueMutex );
      // stop us busy-waiting
      streaming = cameraInfo->isStreaming;
      if ( !streaming && oaDLListIsEmpty ( cameraInfo->commandQueue )) {
        pthread_cond_wait ( &cameraInfo->commandQueued,
            &cameraInfo->commandQueueMutex );
      }
      pthread_mutex_unlock ( &cameraInfo->commandQueueMutex );
    }
    do {
      command = oaDLListRemoveFromHead ( cameraInfo->commandQueue );
      if ( command ) {
        switch ( command->commandType ) {
          case OA_CMD_CONTROL_GET:
            resultCode = _processGetControl ( camera, command );
            break;
          case OA_CMD_CONTROL_SET:
            resultCode = _processSetControl ( camera, command );
            break;
          default:
            fprintf ( stderr, "Invalid command type %d in controller\n",
                command->commandType );
            resultCode = -OA_ERR_INVALID_CONTROL;
            break;
        }
        if ( command->callback ) {
//fprintf ( stderr, "CONT: command has callback\n" );
        } else {
          pthread_mutex_lock ( &cameraInfo->commandQueueMutex );
          command->completed = 1;
          command->resultCode = resultCode;
          pthread_mutex_unlock ( &cameraInfo->commandQueueMutex );
          pthread_cond_broadcast ( &cameraInfo->commandComplete );
        }
      }
    } while ( command );
  } while ( !exitThread );

  return 0;
}


static int
_processGetControl ( oaCamera* camera, OA_COMMAND* command )
{
  int							control = command->controlId;
  oaControlValue*	valp = command->resultData;
  GP2_STATE*			cameraInfo = camera->_private;
	CameraWidget*		widget = 0;
	const char**		options = 0;
	int							numOptions, i, found;
	const char*			currOption;

	if ( control == OA_CAM_CTRL_MIRROR_LOCKUP ) {
		valp->valueType = OA_CTRL_TYPE_BOOLEAN;
		valp->boolean =
				cameraInfo->customFuncStr[ cameraInfo->mirrorLockupPos ] - '0';
		return OA_ERR_NONE;
	}

	switch ( control ) {
		case OA_CAM_CTRL_WHITE_BALANCE:
			widget = cameraInfo->whiteBalance;
			options = cameraInfo->whiteBalanceOptions;
			numOptions = cameraInfo->numWBOptions;
			break;

		case OA_CAM_CTRL_ISO:
			widget = cameraInfo->iso;
			options = cameraInfo->isoOptions;
			numOptions = cameraInfo->numIsoOptions;
			break;

		case OA_CAM_CTRL_SHUTTER_SPEED:
			widget = cameraInfo->shutterSpeed;
			options = cameraInfo->shutterSpeedOptions;
			numOptions = cameraInfo->numShutterSpeedOptions;
			break;

		case OA_CAM_CTRL_FRAME_FORMAT:
			widget = cameraInfo->frameFormat;
			options = cameraInfo->frameFormatOptions;
			numOptions = cameraInfo->numFrameFormatOptions;
			break;

		default:
			fprintf ( stderr, "Unrecognised control %d in %s\n", control,
          __FUNCTION__ );
			return -OA_ERR_INVALID_CONTROL;
			break;
	}

	// Populate the options if we don't already have them
	if ( !options ) {
		( void ) oaGP2CameraGetMenuString ( camera, control, 0 );
	}

	if ( p_gp_widget_get_value ( widget, &currOption ) != GP_OK ) {
		fprintf ( stderr, "Failed to read value of control %d in %s\n",
				control, __FUNCTION__ );
		return -OA_ERR_CAMERA_IO;
	}

	found = 0;
	for ( i = 0; i < numOptions && !found; i++ ) {
		if ( !strcmp ( currOption, options[i] )) {
			valp->valueType = OA_CTRL_TYPE_MENU;
			valp->int32 = i;
			found = 1;
		}
	}
	if ( !found ) {
		fprintf ( stderr, "Failed to match value of control %d in %s [%s]\n",
				control, __FUNCTION__, currOption );
		return -OA_ERR_CAMERA_IO;
	}

	if ( control == OA_CAM_CTRL_FRAME_FORMAT ) {
		valp->valueType = OA_CTRL_TYPE_DISC_MENU;
		if ( valp->int32 == cameraInfo->jpegOption ) {
			valp->int32 = OA_PIX_FMT_JPEG8;
		} else {
			switch ( cameraInfo->manufacturer ) {
				case CAMERA_MANUF_CANON:
					fprintf ( stderr, "Returning Canon CR2 format, but may be CR3\n" );
					valp->int32 = OA_PIX_FMT_CANON_CR2;
					break;
				case CAMERA_MANUF_NIKON:
					valp->int32 = OA_PIX_FMT_NIKON_NEF;
					break;
				default:
					fprintf ( stderr, "Unknown raw camera format\n" );
					break;
			}
		}
	}

	return OA_ERR_NONE;
}


static int
_processSetControl ( oaCamera* camera, OA_COMMAND* command )
{
  oaControlValue*	valp = command->commandData;
  int							control = command->controlId;
  GP2_STATE*			cameraInfo = camera->_private;
	CameraWidget*		widget = 0;
	const char**		options = 0;
	int							numOptions;
	int							newVal, ret;

	if ( control == OA_CAM_CTRL_MIRROR_LOCKUP ) {
		newVal = valp->boolean;
		cameraInfo->customFuncStr[ cameraInfo->mirrorLockupPos ] =
				newVal ? '1' : '0';
		if ( p_gp_widget_set_value ( cameraInfo->customfuncex,
					cameraInfo->customFuncStr ) != GP_OK ) {
			fprintf ( stderr, "Failed to set value of control %d to '%s' in %s\n",
					control, cameraInfo->customFuncStr, __FUNCTION__ );
			return -OA_ERR_CAMERA_IO;
		}
	} else {
		switch ( control ) {
			case OA_CAM_CTRL_WHITE_BALANCE:
				widget = cameraInfo->whiteBalance;
				options = cameraInfo->whiteBalanceOptions;
				numOptions = cameraInfo->numWBOptions;
				break;

			case OA_CAM_CTRL_ISO:
				widget = cameraInfo->iso;
				options = cameraInfo->isoOptions;
				numOptions = cameraInfo->numIsoOptions;
				break;

			case OA_CAM_CTRL_SHUTTER_SPEED:
				widget = cameraInfo->shutterSpeed;
				options = cameraInfo->shutterSpeedOptions;
				numOptions = cameraInfo->numShutterSpeedOptions;
				break;

			case OA_CAM_CTRL_FRAME_FORMAT:
				widget = cameraInfo->frameFormat;
				options = cameraInfo->frameFormatOptions;
				numOptions = cameraInfo->numFrameFormatOptions;
				break;

			default:
				fprintf ( stderr, "Unrecognised control %d in %s\n", control,
          __FUNCTION__ );
				return -OA_ERR_INVALID_CONTROL;
				break;
		}

		newVal = valp->menu;
		if ( control == OA_CAM_CTRL_FRAME_FORMAT ) {
			switch ( newVal ) {
				case OA_PIX_FMT_CANON_CR2:
				case OA_PIX_FMT_CANON_CR3:
				case OA_PIX_FMT_NIKON_NEF:
					newVal = cameraInfo->rawOption;
					break;
				case OA_PIX_FMT_JPEG8:
					newVal = cameraInfo->jpegOption;
					break;
				default:
					return -OA_ERR_OUT_OF_RANGE;
					break;
			}
		} else {
			if ( newVal < 0 || newVal >= numOptions ) {
				return -OA_ERR_OUT_OF_RANGE;
			}
		}

		// Populate the options if we don't already have them
		if ( !options ) {
			( void ) oaGP2CameraGetMenuString ( camera, control, 0 );
		}

		if ( p_gp_widget_set_value ( widget, options[newVal] ) != GP_OK ) {
			fprintf ( stderr, "Failed to set value of control %d in %s\n",
					control, __FUNCTION__ );
			return -OA_ERR_CAMERA_IO;
		}
	}

	if (( ret = p_gp_camera_set_config ( cameraInfo->handle,
			cameraInfo->rootWidget, cameraInfo->ctx )) != GP_OK ) {
		fprintf ( stderr, "Failed to write config to camera in %s, error %d\n",
				__FUNCTION__, ret );
		return -OA_ERR_CAMERA_IO;
	}

	return OA_ERR_NONE;
}
