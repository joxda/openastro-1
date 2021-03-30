/*****************************************************************************
 *
 * logging.c -- Handle logging
 *
 * Copyright 2021 James Fidell (james@openastroproject.org)
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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <oa_common.h>
#include <openastro/util.h>

static unsigned int oaLogLevel = OA_LOG_NONE;
static unsigned int oaLogType = OA_LOG_NONE;
static unsigned int	oaLogToStderr = 1;
static char oaLogFile[ PATH_MAX+1 ];

void
oaSetLogLevel ( unsigned int logLevel )
{
	if ( logLevel > OA_LOG_DEBUG ) {
		logLevel = OA_LOG_DEBUG;
	}
	oaLogLevel = logLevel;
}


int
oaSetLogType ( unsigned int logType )
{
	if ( logType > OA_LOG_TYPE_MAX ) {
		return -OA_ERR_OUT_OF_RANGE;
	}
	oaLogType = logType;
	return OA_ERR_NONE;
}


int
oaAddLogType ( unsigned int logType )
{
	unsigned int n;

	n = oaLogType | logType;
	if ( n > OA_LOG_TYPE_MAX ) {
		return -OA_ERR_OUT_OF_RANGE;
	}
	oaLogType = n;
	return OA_ERR_NONE;
}


int
RemoveLogType ( unsigned int logType )
{
	oaLogType &= ~logType;
	return OA_ERR_NONE;
}


int
oaSetLogFile ( const char* logFile )
{
	FILE*		fp;

	if ( !strcmp ( logFile, "-" )) {
		oaLogToStderr = 1;
		return OA_ERR_NONE;
	}
	if (!( fp = fopen ( logFile, "a" ))) {
		return -OA_ERR_NOT_WRITEABLE;
	}

	fclose ( fp );
	return OA_ERR_NONE;
}


int
oaLogError ( unsigned int logType, const char* str, ... )
{
	FILE*		fp;
	va_list	args;

	if ( oaLogLevel >= OA_LOG_ERROR && ( oaLogType & logType )) {
		if ( oaLogToStderr ) {
			fp = stderr;
		} else {
			if (!( fp = fopen ( oaLogFile, "a" ))) {
				return -OA_ERR_NOT_WRITEABLE;
			}
		}
		fprintf ( fp, "[E] " );
		va_start ( args, str );
		vfprintf ( fp, str, args );
		va_end ( args );
		fprintf ( fp, "\n" );
		fflush ( fp );
		if ( !oaLogToStderr ) {
			fclose ( fp );
		}
	}
	return OA_ERR_NONE;
}


int
oaLogWarning ( unsigned int logType, const char* str, ... )
{
	FILE*		fp;
	va_list	args;

	if ( oaLogLevel >= OA_LOG_WARN && ( oaLogType & logType )) {
		if ( oaLogToStderr ) {
			fp = stderr;
		} else {
			if (!( fp = fopen ( oaLogFile, "a" ))) {
				return -OA_ERR_NOT_WRITEABLE;
			}
		}
		fprintf ( fp, "[W] " );
		va_start ( args, str );
		vfprintf ( fp, str, args );
		va_end ( args );
		fprintf ( fp, "\n" );
		fflush ( fp );
		if ( !oaLogToStderr ) {
			fclose ( fp );
		}
	}
	return OA_ERR_NONE;
}


int
oaLogInfo ( unsigned int logType, const char* str, ... )
{
	FILE*		fp;
	va_list	args;

	if ( oaLogLevel >= OA_LOG_INFO && ( oaLogType & logType )) {
		if ( oaLogToStderr ) {
			fp = stderr;
		} else {
			if (!( fp = fopen ( oaLogFile, "a" ))) {
				return -OA_ERR_NOT_WRITEABLE;
			}
		}
		fprintf ( fp, "[I] " );
		va_start ( args, str );
		vfprintf ( fp, str, args );
		va_end ( args );
		fprintf ( fp, "\n" );
		fflush ( fp );
		if ( !oaLogToStderr ) {
			fclose ( fp );
		}
	}
	return OA_ERR_NONE;
}


int
oaLogDebug ( unsigned int logType, const char* str, ... )
{
	FILE*		fp;
	va_list	args;

	if ( oaLogLevel >= OA_LOG_DEBUG && ( oaLogType & logType )) {
		if ( oaLogToStderr ) {
			fp = stderr;
		} else {
			if (!( fp = fopen ( oaLogFile, "a" ))) {
				return -OA_ERR_NOT_WRITEABLE;
			}
		}
		fprintf ( fp, "[D] " );
		va_start ( args, str );
		vfprintf ( fp, str, args );
		va_end ( args );
		fprintf ( fp, "\n" );
		fflush ( fp );
		if ( !oaLogToStderr ) {
			fclose ( fp );
		}
	}
	return OA_ERR_NONE;
}
