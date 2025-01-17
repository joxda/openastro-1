/*****************************************************************************
 *
 * QHY5IIcontroller.c -- Main camera controller thread
 *
 * Copyright 2015,2017,2018,2019,2021
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

#if HAVE_MATH_H
#include <math.h>
#endif

#include "oacamprivate.h"
#include "unimplemented.h"
#include "QHY.h"
#include "QHYoacam.h"
#include "QHYstate.h"
#include "QHY5II.h"
#include "QHYusb.h"


static int	_processSetControl ( QHY_STATE*, OA_COMMAND* );
static int	_processGetControl ( QHY_STATE*, OA_COMMAND* );
static int	_processSetResolution ( oaCamera*, OA_COMMAND* );
static int	_processStreamingStart ( oaCamera*, OA_COMMAND* );
static int	_processStreamingStop ( QHY_STATE*, OA_COMMAND* );
static int	_doSetGain ( QHY_STATE*, unsigned int );
static int	_doSetHighSpeed ( QHY_STATE*, unsigned int );
static int	_doSetUSBTraffic ( QHY_STATE*, unsigned int );
static int	_doSetExposure ( QHY_STATE*, unsigned int );
static int	_doSetResolution ( QHY_STATE*, int, int );
static void     _processPayload ( oaCamera*, unsigned char*, unsigned int );
static void     _releaseFrame ( QHY_STATE* );


void*
oacamQHY5IIcontroller ( void* param )
{
  oaCamera*		camera = param;
  QHY_STATE*		cameraInfo = camera->_private;
  OA_COMMAND*		command;
  int			exitThread = 0;
  int			resultCode, streaming = 0;

  do {
    pthread_mutex_lock ( &cameraInfo->commandQueueMutex );
    exitThread = cameraInfo->stopControllerThread;
    pthread_mutex_unlock ( &cameraInfo->commandQueueMutex );
    if ( exitThread ) {
      break;
    } else {
      pthread_mutex_lock ( &cameraInfo->commandQueueMutex );
      // stop us busy-waiting
      streaming = ( cameraInfo->runMode == CAM_RUN_MODE_STREAMING ) ? 1 : 0;
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
          case OA_CMD_CONTROL_SET:
            resultCode = _processSetControl ( cameraInfo, command );
            break;
          case OA_CMD_CONTROL_GET:
            resultCode = _processGetControl ( cameraInfo, command );
            break;
          case OA_CMD_RESOLUTION_SET:
            resultCode = _processSetResolution ( camera, command );
            break;
          case OA_CMD_START_STREAMING:
            resultCode = _processStreamingStart ( camera, command );
            break;
          case OA_CMD_STOP_STREAMING:
            resultCode = _processStreamingStop ( cameraInfo, command );
            break;
          default:
            oaLogError ( OA_LOG_CAMERA, "%s: Invalid command type %d",
								__func__, command->commandType );
            resultCode = -OA_ERR_INVALID_CONTROL;
            break;
        }
        if ( command->callback ) {
					oaLogError ( OA_LOG_CAMERA, "%s: command has callback", __func__ );
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
_processSetControl ( QHY_STATE* cameraInfo, OA_COMMAND* command )
{
  oaControlValue	*valp = command->commandData;
  int			control = command->controlId;

  int32_t val_s32;
  int64_t val_s64;

	oaLogInfo ( OA_LOG_CAMERA, "%s ( %p, %p ): entered", __func__, cameraInfo,
			command );
	oaLogDebug ( OA_LOG_CAMERA, "%s: control = %d", __func__, control );

  switch ( control ) {

    case OA_CAM_CTRL_GAIN:
      if ( valp->valueType != OA_CTRL_TYPE_INT32 ) {
        oaLogError ( OA_LOG_CAMERA,
						"%s: invalid control type %d where int32 expected", __func__,
            valp->valueType );
        return -OA_ERR_INVALID_CONTROL_TYPE;
      }
      if ( valp->int32 < 0 ) {
        return -OA_ERR_OUT_OF_RANGE;
      }
      cameraInfo->currentGain = valp->int32;
      _doSetGain ( cameraInfo, cameraInfo->currentGain );
      break;

    case OA_CAM_CTRL_EXPOSURE_ABSOLUTE:
      if ( valp->valueType != OA_CTRL_TYPE_INT64 ) {
        oaLogError ( OA_LOG_CAMERA,
						"%s: invalid control type %d where int64 expected", __func__,
            valp->valueType );
        return -OA_ERR_INVALID_CONTROL_TYPE;
      }
      val_s64 = valp->int64;
      if ( val_s64 < 1 ) { val_s64 = 1; }
      cameraInfo->currentExposure = val_s64;
      _doSetExposure ( cameraInfo, val_s64 / 1000 );
      break;

    case OA_CAM_CTRL_HIGHSPEED:
      if ( valp->valueType != OA_CTRL_TYPE_BOOLEAN ) {
        oaLogError ( OA_LOG_CAMERA,
						"%s: invalid control type %d where bool expected", __func__,
            valp->valueType );
        return -OA_ERR_INVALID_CONTROL_TYPE;
      }
      val_s32 = valp->boolean;

      cameraInfo->currentHighSpeed = val_s32;
      _doSetHighSpeed ( cameraInfo, cameraInfo->currentHighSpeed );
      break;

    case OA_CAM_CTRL_USBTRAFFIC:
      if ( valp->valueType != OA_CTRL_TYPE_INT32 ) {
        oaLogError ( OA_LOG_CAMERA,
						"%s: invalid control type %d where int32 expected", __func__,
            valp->valueType );
        return -OA_ERR_INVALID_CONTROL_TYPE;
      }
      val_s32 = valp->int32;
      if ( val_s32 < 0 ) {
        return -OA_ERR_OUT_OF_RANGE;
      }
      cameraInfo->currentUSBTraffic = val_s32;
      _doSetUSBTraffic ( cameraInfo, cameraInfo->currentUSBTraffic );
      break;

    case OA_CAM_CTRL_DROPPED_RESET:
      // droppedFrames could be mutexed, but it's not the end of the world
      cameraInfo->droppedFrames = 0;
      break;

    case OA_CAM_CTRL_FRAME_FORMAT:
      // Nothing to be done here
      break;

    default:
      oaLogError ( OA_LOG_CAMERA, "%s: unrecognised control %d", __func__,
					control );
      return -OA_ERR_INVALID_CONTROL;
      break;
  }

	oaLogInfo ( OA_LOG_CAMERA, "%s: exiting", __func__ );

  return OA_ERR_NONE;
}


static int
_doSetGain ( QHY_STATE* cameraInfo, unsigned int gain )
{
 /*
  static const int      gainLookup[] = {
      0x000,0x004,0x005,0x006,0x007,0x008,0x009,0x00A,0x00B,0x00C,0x00D,0x00E,
      0x00F,0x010,0x011,0x012,0x013,0x014,0x015,0x016,0x017,0x018,0x019,0x01A,
      0x01B,0x01C,0x01D,0x01E,0x01F,0x051,0x052,0x053,0x054,0x055,0x056,0x057,
      0x058,0x059,0x05A,0x05B,0x05C,0x05D,0x05E,0x05F,0x6CE,0x6CF,0x6D0,0x6D1,
      0x6D2,0x6D3,0x6D4,0x6D5,0x6D6,0x6D7,0x6D8,0x6D9,0x6DA,0x6DB,0x6DC,0x6DD,
      0x6DE,0x6DF,0x6E0,0x6E1,0x6E2,0x6E3,0x6E4,0x6E5,0x6E6,0x6E7,0x6FC,0x6FD,
      0x6FE,0x6FF
  };
  */

  static const int      gainLookup[] = {
      0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,0x10,0x11,0x12,0x13,
      0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,
      0x20,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5A,0x5B,
      0x5C,0x5D,0x5E,0x5F,0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67
  };


	oaLogInfo ( OA_LOG_CAMERA, "%s ( %p, %d ): entered", __func__, cameraInfo,
			gain );

  _i2cWrite16 ( cameraInfo, MT9M001_GLOBAL_GAIN,
      gainLookup[ gain - QHY5II_MONO_GAIN_MIN ]);

	oaLogInfo ( OA_LOG_CAMERA, "%s: exiting", __func__ );

  return OA_ERR_NONE;
}


static int
_doSetHighSpeed ( QHY_STATE* cameraInfo, unsigned int value )
{
  unsigned char	buf;

	oaLogInfo ( OA_LOG_CAMERA, "%s ( %p, %d ): entered", __func__, cameraInfo,
			value );

  if ( value ) {
    cameraInfo->CMOSClock = 48;
    buf = 2;
  } else {
    cameraInfo->CMOSClock = 24;
    buf = 1;
  }

  _usbControlMsg ( cameraInfo, QHY_CMD_DEFAULT_OUT, 0xc8, 0, 0, &buf, 1, 0 );

	oaLogInfo ( OA_LOG_CAMERA, "%s: exiting", __func__ );

  return OA_ERR_NONE;
}


static int
_doSetUSBTraffic ( QHY_STATE* cameraInfo, unsigned int value )
{
	oaLogInfo ( OA_LOG_CAMERA, "%s ( %p, %d ): entered", __func__, cameraInfo,
			value );

  _i2cWrite16 ( cameraInfo, MT9M001_HORIZ_BLANKING, 9 + value * 50 );

	oaLogInfo ( OA_LOG_CAMERA, "%s: exiting", __func__ );

  return OA_ERR_NONE;
}


static int
_doSetExposure ( QHY_STATE* cameraInfo, unsigned int value )
{
  double		pixelTime, rowTime, maxShortExposureTime;
  unsigned short	columnSize, horizBlanking, shutterWidth;
  unsigned short	shutterDelay, activeDataTime, frameStartBlanking;
  unsigned short	frameEndBlanking, horizontalBlanking, rowPixelClocks;
  unsigned long		newTimeMillisec, newTimeMicrosec;
  unsigned char		buf[4];

	oaLogInfo ( OA_LOG_CAMERA, "%s ( %p, %d ): entered", __func__, cameraInfo,
			value );

  /*
   * The intent of this appears to be to set the exposure time to zero,
   * but I don't know that it's necessary
  buf[0] = buf[1] = buf[2] = buf[3] = 0;
  _usbControlMsg ( cameraInfo, QHY_CMD_DEFAULT_OUT, 0xc1, 0, 0, buf, 4, 0 );
  usleep ( 10000 );
  _i2cWrite16 ( cameraInfo, MT9M001_SHUTTER_WIDTH, 0 );
  usleep ( 100000 );
  */

  pixelTime = 1.0 / cameraInfo->CMOSClock;
  columnSize = _i2cRead16 ( cameraInfo, MT9M001_COLUMN_SIZE );
  horizBlanking = _i2cRead16 ( cameraInfo, MT9M001_HORIZ_BLANKING );
  shutterWidth = _i2cRead16 ( cameraInfo, MT9M001_SHUTTER_WIDTH );
  shutterDelay = _i2cRead16 ( cameraInfo, MT9M001_SHUTTER_DELAY );

  // Lots of these numbers come from the MT9M001 datasheet
  activeDataTime = columnSize + 1;
  frameStartBlanking = 242;
  frameEndBlanking = 2 + horizBlanking - 19;
  horizontalBlanking = frameStartBlanking + frameEndBlanking;
  rowPixelClocks = activeDataTime + horizontalBlanking;
  rowTime = rowPixelClocks * pixelTime;
  maxShortExposureTime = 15000 * rowTime - 180 * pixelTime - 4 * shutterDelay *
      pixelTime;
  newTimeMicrosec = value * 1000;

  if ( newTimeMicrosec > maxShortExposureTime ) {
    // FIX ME -- does this actually do anything?
    cameraInfo->longExposureMode = 1;
    _i2cWrite16 ( cameraInfo, MT9M001_SHUTTER_WIDTH, 15000 );
    newTimeMillisec = ( newTimeMicrosec - maxShortExposureTime ) / 1000;
    buf[0] = 0;
    buf[1] = ( newTimeMillisec >> 16 ) & 0xff;
    buf[2] = ( newTimeMillisec >> 8 ) & 0xff;
    buf[3] = newTimeMillisec & 0xff;
    _usbControlMsg ( cameraInfo, QHY_CMD_DEFAULT_OUT, 0xc1, 0, 0, buf, 4, 0 );
  } else {
    cameraInfo->longExposureMode = 0;
    buf[0] = buf[1] = buf[2] = buf[3] = 0;
    _usbControlMsg ( cameraInfo, QHY_CMD_DEFAULT_OUT, 0xc1, 0, 0, buf, 4, 0 );
    usleep ( 1000 );
    shutterWidth = ( newTimeMicrosec + 180 * pixelTime + 4 * shutterDelay *
        pixelTime ) / rowTime;
    if ( shutterWidth < 1 ) {
      shutterWidth = 1;
    }
    _i2cWrite16 ( cameraInfo, MT9M001_SHUTTER_WIDTH, shutterWidth );
  }

	oaLogInfo ( OA_LOG_CAMERA, "%s: exiting", __func__ );

  return OA_ERR_NONE;
}


void
oaQHY5IISetAllControls ( QHY_STATE* cameraInfo )
{
	oaLogInfo ( OA_LOG_CAMERA, "%s ( %p ): entered", __func__, cameraInfo );

  _doSetUSBTraffic ( cameraInfo, cameraInfo->currentUSBTraffic );
  _doSetHighSpeed ( cameraInfo, cameraInfo->currentHighSpeed );
  _doSetResolution ( cameraInfo, cameraInfo->xSize, cameraInfo->ySize );
  _doSetExposure ( cameraInfo, cameraInfo->currentExposure );
  _doSetGain ( cameraInfo, cameraInfo->currentGain );
  _doSetUSBTraffic ( cameraInfo, cameraInfo->currentUSBTraffic );
  _doSetExposure ( cameraInfo, cameraInfo->currentExposure );

	oaLogInfo ( OA_LOG_CAMERA, "%s: exiting", __func__ );
}


static int
_processSetResolution ( oaCamera* camera, OA_COMMAND* command )
{
  QHY_STATE*	cameraInfo = camera->_private;
  FRAMESIZE*	size = command->commandData;

  cameraInfo->xSize = size->x;
  cameraInfo->ySize = size->y;

  _doSetResolution ( cameraInfo, cameraInfo->xSize, cameraInfo->ySize );
  _doSetExposure ( cameraInfo, cameraInfo->currentExposure );
  _doSetGain ( cameraInfo, cameraInfo->currentGain );
  return OA_ERR_NONE;
}

static int
_doSetResolution ( QHY_STATE* cameraInfo, int x, int y )
{
  unsigned int	xStart, yStart;

	oaLogInfo ( OA_LOG_CAMERA, "%s ( %p, %d, %d ): entered", __func__, cameraInfo,
			x, y );

  xStart = 12 + ( QHY5II_IMAGE_WIDTH - x ) / 2;
  yStart = 20 + ( QHY5II_IMAGE_HEIGHT - y ) / 2;

  // _i2cWrite16 ( cameraInfo, MT9M001_SHUTTER_WIDTH, 200 );
  _i2cWrite16 ( cameraInfo, MT9M001_ROW_START, yStart );
  _i2cWrite16 ( cameraInfo, MT9M001_COLUMN_START, xStart );
  _i2cWrite16 ( cameraInfo, MT9M001_ROW_SIZE, y - 1 );
  _i2cWrite16 ( cameraInfo, MT9M001_COLUMN_SIZE, x - 1 );
  _i2cWrite16 ( cameraInfo, 0x22, 0 );
  _i2cWrite16 ( cameraInfo, 0x23, 0 );

  cameraInfo->frameSize = x * y;
  cameraInfo->captureLength = cameraInfo->frameSize + QHY5II_EOF_LEN;

	oaLogInfo ( OA_LOG_CAMERA, "%s: exiting", __func__ );

  return OA_ERR_NONE;
}


static int
_processGetControl ( QHY_STATE* cameraInfo, OA_COMMAND* command )
{
  int			control = command->controlId;
  oaControlValue*	valp = command->resultData;

	oaLogInfo ( OA_LOG_CAMERA, "%s ( %p, %p ): entered", __func__, cameraInfo,
			command );
	oaLogDebug ( OA_LOG_CAMERA, "%s: control = %d", __func__, control );

  switch ( control ) {

    case OA_CAM_CTRL_GAIN:
      valp->valueType = OA_CTRL_TYPE_INT32;
      valp->int32 = cameraInfo->currentGain;
      break;

    case OA_CAM_CTRL_EXPOSURE_ABSOLUTE:
      valp->valueType = OA_CTRL_TYPE_INT64;
      valp->int64 = cameraInfo->currentExposure;
      break;

    case OA_CAM_CTRL_HIGHSPEED:
      valp->valueType = OA_CTRL_TYPE_BOOLEAN;
      valp->boolean = cameraInfo->currentHighSpeed;
      break;

    case OA_CAM_CTRL_USBTRAFFIC:
      valp->valueType = OA_CTRL_TYPE_INT32;
      valp->int32 = cameraInfo->currentUSBTraffic;
      break;

    case OA_CAM_CTRL_DROPPED:
      valp->valueType = OA_CTRL_TYPE_READONLY;
      valp->readonly = cameraInfo->droppedFrames;
      break;

    default:
      oaLogError ( OA_LOG_CAMERA, "%s: Unimplemented control %d", __func__,
					control );
      return -OA_ERR_INVALID_CONTROL;
      break;
  }

	oaLogInfo ( OA_LOG_CAMERA, "%s: exiting", __func__ );

  return OA_ERR_NONE;
}


libusb_transfer_cb_fn
_qhy5iiVideoStreamCallback ( struct libusb_transfer* transfer )
{
  oaCamera*     camera = transfer->user_data;
  QHY_STATE*    cameraInfo = camera->_private;
  int           resubmit = 1, streaming;

  switch ( transfer->status ) {

    case LIBUSB_TRANSFER_COMPLETED:
      if ( transfer->num_iso_packets == 0 ) { // bulk mode transfer
        _processPayload ( camera, transfer->buffer, transfer->actual_length );
      } else {
        oaLogWarning ( OA_LOG_CAMERA, "%s: Unexpected isochronous transfer",
						__func__ );
      }
      break;

    case LIBUSB_TRANSFER_CANCELLED:
    case LIBUSB_TRANSFER_ERROR:
    case LIBUSB_TRANSFER_NO_DEVICE:
    {
      int i;

      pthread_mutex_lock ( &cameraInfo->videoCallbackMutex );

      for ( i = 0; i < QHY_NUM_TRANSFER_BUFS; i++ ) {
        if ( cameraInfo->transfers[i] == transfer ) {
          free ( transfer->buffer );
          libusb_free_transfer ( transfer );
          cameraInfo->transfers[i] = 0;
          break;
        }
      }

      if ( QHY_NUM_TRANSFER_BUFS == i ) {
        oaLogWarning ( OA_LOG_CAMERA,
						"%s: transfer %p not found; not freeing!", __func__, transfer );
      }

      resubmit = 0;

      pthread_mutex_unlock ( &cameraInfo->videoCallbackMutex );
      break;
    }
    case LIBUSB_TRANSFER_TIMED_OUT:
      break;

    case LIBUSB_TRANSFER_STALL:
    case LIBUSB_TRANSFER_OVERFLOW:
      oaLogWarning ( OA_LOG_CAMERA, "%s: retrying transfer, status = %d (%s)",
					__func__, transfer->status, libusb_error_name ( transfer->status ));
      break;
  }

  if ( resubmit ) {
    pthread_mutex_lock ( &cameraInfo->commandQueueMutex );
    streaming = ( cameraInfo->runMode == CAM_RUN_MODE_STREAMING ) ? 1 : 0;
    pthread_mutex_unlock ( &cameraInfo->commandQueueMutex );
    if ( streaming ) {
      libusb_submit_transfer ( transfer );
    } else {
      int i;
      pthread_mutex_lock ( &cameraInfo->videoCallbackMutex );
      // Mark transfer deleted
      for ( i = 0; i < QHY_NUM_TRANSFER_BUFS; i++ ) {
        if ( cameraInfo->transfers[i] == transfer ) {
          oaLogWarning ( OA_LOG_CAMERA, "%s: Freeing orphan transfer %d (%p)",
							__func__, i, transfer );
          free ( transfer->buffer );
          libusb_free_transfer ( transfer );
          cameraInfo->transfers[i] = 0;
        }
      }
      if ( QHY_NUM_TRANSFER_BUFS == i ) {
        oaLogWarning ( OA_LOG_CAMERA,
						"%s: orphan transfer %p not found; not freeing!", __func__,
            transfer );
      }
      pthread_mutex_unlock ( &cameraInfo->videoCallbackMutex );
    }
  }

  return 0;
}


static int
_processStreamingStart ( oaCamera* camera, OA_COMMAND* command )
{
  QHY_STATE*	                cameraInfo = camera->_private;
  CALLBACK*	                cb = command->commandData;
  int                           txId, ret, txBufferSize, numTxBuffers;
  struct libusb_transfer*       transfer;
  unsigned char			buf[1] = { 100 };

  if ( cameraInfo->runMode != CAM_RUN_MODE_STOPPED ) {
    return -OA_ERR_INVALID_COMMAND;
  }

  cameraInfo->streamingCallback.callback = cb->callback;
  cameraInfo->streamingCallback.callbackArg = cb->callbackArg;

  txBufferSize = cameraInfo->captureLength;
  // This is a guess
  numTxBuffers = 8;
  if ( numTxBuffers < 8 ) {
    numTxBuffers = 8;
  }
  if ( numTxBuffers > 100 ) {
    numTxBuffers = 100;
  }
  for ( txId = 0; txId < QHY_NUM_TRANSFER_BUFS; txId++ ) {
    if ( txId < numTxBuffers ) {
      transfer = libusb_alloc_transfer(0);
      cameraInfo->transfers[ txId ] = transfer;
      if (!( cameraInfo->transferBuffers [ txId ] =
          malloc ( txBufferSize ))) {
        oaLogError ( OA_LOG_CAMERA, "%s: malloc failed.  Need to free buffer",
						__func__ );
        return -OA_ERR_SYSTEM_ERROR;
      }
      libusb_fill_bulk_transfer ( transfer, cameraInfo->usbHandle,
          QHY_BULK_ENDP_IN, cameraInfo->transferBuffers [ txId ],
          txBufferSize, ( libusb_transfer_cb_fn ) _qhy5iiVideoStreamCallback,
          camera, USB2_TIMEOUT );
    } else {
      cameraInfo->transfers[ txId ] = 0;
    }
  }

  for ( txId = 0; txId < numTxBuffers; txId++ ) {
    if (( ret = libusb_submit_transfer ( cameraInfo->transfers [ txId ]))) {
      break;
    }
  }

  // free up any transfer buffers that we're not using
  if ( ret && txId > 0 ) {
    for ( ; txId < QHY_NUM_TRANSFER_BUFS; txId++) {
      if ( cameraInfo->transfers[ txId ] ) {
        if ( cameraInfo->transfers[ txId ]->buffer ) {
          free ( cameraInfo->transfers[ txId ]->buffer );
        }
        libusb_free_transfer ( cameraInfo->transfers[ txId ]);
        cameraInfo->transfers[ txId ] = 0;
      }
    }
  }

  _usbControlMsg ( cameraInfo, QHY_CMD_DEFAULT_OUT, QHY_REQ_BEGIN_VIDEO,
      0, 0, buf, 1, 0 );

  pthread_mutex_lock ( &cameraInfo->commandQueueMutex );
  cameraInfo->runMode = CAM_RUN_MODE_STREAMING;
  pthread_mutex_unlock ( &cameraInfo->commandQueueMutex );

  return OA_ERR_NONE;
}


static int
_processStreamingStop ( QHY_STATE* cameraInfo, OA_COMMAND* command )
{
  int		queueEmpty, i, res, allReleased;
  unsigned char	buf[4] = { 0, 0, 0, 0 };

  if ( cameraInfo->runMode != CAM_RUN_MODE_STREAMING ) {
    return -OA_ERR_INVALID_COMMAND;
  }

  _usbControlMsg ( cameraInfo, QHY_CMD_DEFAULT_OUT, 0xc1, 0, 0, buf, 4, 0 );

  pthread_mutex_lock ( &cameraInfo->commandQueueMutex );
  cameraInfo->runMode = CAM_RUN_MODE_STOPPED;
  pthread_mutex_unlock ( &cameraInfo->commandQueueMutex );

  pthread_mutex_lock ( &cameraInfo->videoCallbackMutex );
  for ( i = 0; i < QHY_NUM_TRANSFER_BUFS; i++ ) {
    if ( cameraInfo->transfers[i] ) {
      res = libusb_cancel_transfer ( cameraInfo->transfers[i] );
      if ( res < 0 && res != LIBUSB_ERROR_NOT_FOUND ) {
        free ( cameraInfo->transfers[i]->buffer );
        libusb_free_transfer ( cameraInfo->transfers[i] );
        cameraInfo->transfers[i] = 0;
      }
    }
  }
  pthread_mutex_unlock ( &cameraInfo->videoCallbackMutex );

  do {
    allReleased = 1;
    for ( i = 0; i < QHY_NUM_TRANSFER_BUFS && allReleased; i++ ) {
      pthread_mutex_lock ( &cameraInfo->videoCallbackMutex );
      if ( cameraInfo->transfers[i] ) {
        allReleased = 0;
      }
      pthread_mutex_unlock ( &cameraInfo->videoCallbackMutex );
    }
    if ( !allReleased ) {
      usleep ( 100 ); // FIX ME -- lazy.  should use a pthread condition?
    }
  } while ( !allReleased );

  // We wait here until the callback queue has drained otherwise a future
  // close of the camera could rip the image frame out from underneath the
  // callback

  queueEmpty = 0;
  do {
    pthread_mutex_lock ( &cameraInfo->callbackQueueMutex );
    queueEmpty = ( OA_CAM_BUFFERS == cameraInfo->buffersFree ) ? 1 : 0;
    pthread_mutex_unlock ( &cameraInfo->callbackQueueMutex );
    if ( !queueEmpty ) {
      usleep ( 10000 );
    }
  } while ( !queueEmpty );

  return OA_ERR_NONE;
}


static void
_processPayload ( oaCamera* camera, unsigned char* buffer, unsigned int len )
{
  QHY_STATE*            cameraInfo = camera->_private;
  unsigned int          buffersFree, dropFrame;
  unsigned char*        p;

  if ( 0 == len ) {
    return;
  }

  dropFrame = 0;

  pthread_mutex_lock ( &cameraInfo->callbackQueueMutex );
  buffersFree = cameraInfo->buffersFree;
  pthread_mutex_unlock ( &cameraInfo->callbackQueueMutex );
  if ( buffersFree && ( cameraInfo->receivedBytes + len ) <=
      cameraInfo->captureLength ) {
    memcpy (( unsigned char* ) cameraInfo->buffers[
        cameraInfo->nextBuffer ].start + cameraInfo->receivedBytes,
        buffer, len );
    cameraInfo->receivedBytes += len;
    // It seems that the last five bytes of the frame should be
    // 0xaa, 0x11, 0xcc, 0xee, 0xXX
    p = ( unsigned char* ) cameraInfo->buffers[
      cameraInfo->nextBuffer ].start + cameraInfo->receivedBytes -
          QHY5II_EOF_LEN;
    if ( p[0] == 0xaa && p[1] == 0x11 && p[2] == 0xcc && p[3] == 0xee ) {
      if ( cameraInfo->receivedBytes == cameraInfo->captureLength ) {
        _releaseFrame ( cameraInfo );
      } else {
        if ( cameraInfo->receivedBytes == QHY5II_EOF_LEN ) {
          cameraInfo->receivedBytes = 0;
        } else {
          dropFrame = 1;
        }
      }
    }
  } else {
    dropFrame = 1;
  }

  if ( dropFrame ) {
    pthread_mutex_lock ( &cameraInfo->callbackQueueMutex );
    cameraInfo->droppedFrames++;
    cameraInfo->receivedBytes = 0;
    pthread_mutex_unlock ( &cameraInfo->callbackQueueMutex );
  }
}


static void
_releaseFrame ( QHY_STATE* cameraInfo )
{
  int           nextBuffer = cameraInfo->nextBuffer;

  cameraInfo->frameCallbacks[ nextBuffer ].callbackType =
      OA_CALLBACK_NEW_FRAME;
  cameraInfo->frameCallbacks[ nextBuffer ].callback =
      cameraInfo->streamingCallback.callback;
  cameraInfo->frameCallbacks[ nextBuffer ].callbackArg =
      cameraInfo->streamingCallback.callbackArg;
  cameraInfo->frameCallbacks[ nextBuffer ].buffer =
      cameraInfo->buffers[ nextBuffer ].start;
  cameraInfo->frameCallbacks[ nextBuffer ].bufferLen =
      cameraInfo->frameSize;
  pthread_mutex_lock ( &cameraInfo->callbackQueueMutex );
  oaDLListAddToTail ( cameraInfo->callbackQueue,
      &cameraInfo->frameCallbacks[ nextBuffer ]);
  cameraInfo->buffersFree--;
  cameraInfo->nextBuffer = ( nextBuffer + 1 ) % cameraInfo->configuredBuffers;
  cameraInfo->receivedBytes = 0;
  pthread_mutex_unlock ( &cameraInfo->callbackQueueMutex );
  pthread_cond_broadcast ( &cameraInfo->callbackQueued );
}
