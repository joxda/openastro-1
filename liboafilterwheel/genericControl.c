/*****************************************************************************
 *
 * genericControl.c -- Generic filter wheel control functions
 *
 * Copyright 2018 James Fidell (james@openastroproject.org)
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

#include <errno.h>
#include <pthread.h>

#include <openastro/util.h>
#include <openastro/filterwheel.h>
#include <openastro/filterwheel/controls.h>

#include "oafwprivate.h"
#include "unimplemented.h"


int
oaWheelSetControl ( oaFilterWheel* wheel, int control, oaControlValue* val )
{
  OA_COMMAND	command;
  PRIVATE_INFO*	privateInfo = wheel->_private;
  int		retval;

  OA_CLEAR ( command );
  command.commandType = OA_CMD_CONTROL_SET;
  command.controlId = control;
  command.commandData = val;

  oaDLListAddToTail ( privateInfo->commandQueue, &command );
  pthread_cond_broadcast ( &privateInfo->commandQueued );
  pthread_mutex_lock ( &privateInfo->commandQueueMutex );
  while ( !command.completed ) {
    pthread_cond_wait ( &privateInfo->commandComplete,
        &privateInfo->commandQueueMutex );
  }
  pthread_mutex_unlock ( &privateInfo->commandQueueMutex );
  retval = command.resultCode;

  return retval;
}


int
oaWheelReadControl ( oaFilterWheel* wheel, int control, oaControlValue* val )
{
  OA_COMMAND	command;
  PRIVATE_INFO*	wheelInfo = wheel->_private;
  int		retval;

  // Could do more validation here, but it's a bit messy to do here
  // and in the controller too.

  OA_CLEAR ( command );
  command.commandType = OA_CMD_CONTROL_GET;
  command.controlId = control;
  command.resultData = val;

  oaDLListAddToTail ( wheelInfo->commandQueue, &command );
  pthread_cond_broadcast ( &wheelInfo->commandQueued );
  pthread_mutex_lock ( &wheelInfo->commandQueueMutex );
  while ( !command.completed ) {
    pthread_cond_wait ( &wheelInfo->commandComplete,
        &wheelInfo->commandQueueMutex );
  }
  pthread_mutex_unlock ( &wheelInfo->commandQueueMutex );
  retval = command.resultCode;

  return retval;
}

/*
int
oaWheelTestControl ( oaFilterWheel* wheel, int control, oaControlValue* val )
{
  uint32_t      val_u32;
  int64_t       val_s64;
  COMMON_INFO*  commonInfo = wheel->_common;

  if ( !wheel->controls [ control ] ) {
    return -OA_ERR_INVALID_CONTROL;
  }

  if ( wheel->controls [ control ] != val->valueType ) {
    return -OA_ERR_INVALID_CONTROL_TYPE;
  }

  // FIX ME -- there's lots more validation to be done here

  // And if we reach here it's because the value wasn't valid
  return -OA_ERR_OUT_OF_RANGE;
}
*/
