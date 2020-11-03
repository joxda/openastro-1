/*****************************************************************************
 *
 * oacam.c -- main entrypoint for Basler Pylon support
 *
 * Copyright 2020
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

#include <pylonc/PylonC.h>

#include <openastro/camera.h>
#include <openastro/demosaic.h>

#include "oacamprivate.h"
#include "unimplemented.h"
#include "oacam.h"


/**
 * Cycle through the list of cameras returned by the Pylon library
 */

int
oaPylonGetCameras ( CAMERA_LIST* deviceList, unsigned long featureFlags,
		int flags )
{
	GENAPIC_RESULT				ret;
	PYLON_DEVICE_HANDLE		deviceHandle;
  unsigned int					i, numFound = 0;
	char									buffer[256];
	size_t								size, numCameras;
	oaCameraDevice*				dev;
	DEVICE_INFO*					_private;

	PylonInitialize();

	if ( PylonEnumerateDevices( &numCameras ) != GENAPI_E_OK ) {
		fprintf ( stderr, "Can't enumerate Basler devices\n" );
		PylonTerminate();
		return -OA_ERR_SYSTEM_ERROR;
	}

  if ( !numCameras ) {
    PylonTerminate();
    return 0;
  }

  for ( i = 0; i < numCameras; i++ ) {
		if ( PylonCreateDeviceByIndex ( i, &deviceHandle ) != GENAPI_E_OK ) {
			fprintf ( stderr, "Error creating Basler device by index\n" );
			PylonTerminate();
			return -OA_ERR_SYSTEM_ERROR;
		}

		if ( PylonDeviceOpen ( deviceHandle, PYLONC_ACCESS_MODE_CONTROL ) !=
				GENAPI_E_OK ) {
			fprintf ( stderr, "Error opening Basler device %d\n", i );
			PylonTerminate();
			return -OA_ERR_SYSTEM_ERROR;
		}

		if ( PylonDeviceFeatureIsReadable ( deviceHandle, "DeviceModelName" )) {
			size = sizeof ( buffer );
			if ( PylonDeviceFeatureToString ( deviceHandle, "DeviceModelName",
					buffer, &size ) != GENAPI_E_OK ) {
				fprintf ( stderr, "Reading Basler DeviceModelName failed" );
				PylonDeviceClose ( deviceHandle );
				PylonTerminate();
				return -OA_ERR_SYSTEM_ERROR;
			}
		} else {
			( void ) strcpy ( buffer, "unknown camera" );
		}

		PylonDeviceClose ( deviceHandle );

    if (!( dev = malloc ( sizeof ( oaCameraDevice )))) {
			_oaFreeCameraDeviceList ( deviceList );
			PylonTerminate();
      return -OA_ERR_MEM_ALLOC;
    }

    if (!( _private = malloc ( sizeof ( DEVICE_INFO )))) {
      ( void ) free (( void* ) dev );
			PylonTerminate();
      return -OA_ERR_MEM_ALLOC;
    }

    _oaInitCameraDeviceFunctionPointers ( dev );
    dev->interface = OA_CAM_IF_PYLON;
    ( void ) strncpy ( dev->deviceName, buffer, OA_MAX_NAME_LEN );
    dev->_private = _private;
    // dev->initCamera = oaPylonInitCamera;

    if (( ret = _oaCheckCameraArraySize ( deviceList )) < 0 ) {
      ( void ) free (( void* ) dev );
      ( void ) free (( void* ) _private );
			PylonTerminate();
      return ret;
    }
    deviceList->cameraList[ deviceList->numCameras++ ] = dev;
    numFound++;
  }

	PylonTerminate();
  return numFound;
}
