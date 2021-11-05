cmake_minimum_required(VERSION 3.14)

project(oalib LANGUAGES C CXX)

SET( CMAKE_C_STANDARD 99 )
SET( CMAKE_CXX_STANDARD 11 )
cmake_policy(SET CMP0075 NEW)

# possibly put checks in separate file?
# use internal alternatives?
# libraries: want to include vs available?
# qhyccd special stuff see below
# TBD udev?

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/TargetArch.cmake)
target_architecture(arch)
message(${arch})

#checkQtForPIC=no

SET(CHECKSYSTEMLIBTOUPCAM FALSE)
SET(CHECKSYSTEMLIBUSB FALSE)
SET(CHECKSYSTEMDC1394 FALSE)
SET(CHECKSYSTEMLIBUVC FALSE)
SET(CHECKSYSTEMLIBUSB FALSE)
SET(CHECKSYSTEMLIBHIDAPI FALSE)
SET(CHECKSYSTEMLIBALTAIRCAM FALSE)
SET(CHECKSYSTEMLIBALTAIRCAMLEGACY FALSE)
SET(CHECKSYSTEMLIBSTARSHOOTG FALSE)
SET(CHECKSYSTEMLIBNNCAM FALSE)
SET(CHECKSYSTEMLIBMALLNCAM FALSE)
SET(CHECKSYSTEMLIBOMEGONPROCAM FALSE)
SET(CHECKSYSTEMLIBQHYCCD FALSE)
SET(CHECKSYSTEMLIBMEADECAM FALSE)
SET(CHECKSYSTEMLIBSVBCAMERASDK FALSE)
SET(CHECKSYSTEMLIBSASICAMERA FALSE)

#checkSystemLibefwfilter=no

IF(APPLE)
    SET(USB_OVERFLOW_HANGS TRUE)
    SET(HAVE_SVBCAMERASDK TRUE)
    SET(BUILD_LIBUSB TRUE)

    file(CREATE_LINK ${CMAKE_CURRENT_SOURCE_DIR}/ext/libASICamera2/mac/libASICamera2.dylib ${CMAKE_CURRENT_SOURCE_DIR}/ext/libASICamera2/libASICamera2.dylib SYMBOLIC)
    file(CREATE_LINK ${CMAKE_CURRENT_SOURCE_DIR}/ext/libtoupcam/mac/libtoupcam.dylib ${CMAKE_CURRENT_SOURCE_DIR}/ext/libtoupcam/libtoupcam.dylib SYMBOLIC)
    file(CREATE_LINK ${CMAKE_CURRENT_SOURCE_DIR}/ext/libaltaircam/mac64/libaltaircam.dylib ${CMAKE_CURRENT_SOURCE_DIR}/ext/libaltaircam/libaltaircam.dylib SYMBOLIC)
    file(CREATE_LINK ${CMAKE_CURRENT_SOURCE_DIR}/ext/libaltaircamlegacy/mac64/libaltaircam.dylib ${CMAKE_CURRENT_SOURCE_DIR}/ext/libaltaircamlegacy/libaltaircamlegacy.dylib SYMBOLIC)
    file(CREATE_LINK ${CMAKE_CURRENT_SOURCE_DIR}/ext/libqhyccd/mac64/libqhyccd.dylib ${CMAKE_CURRENT_SOURCE_DIR}/ext/libqhyccd/libqhyccd.dylib SYMBOLIC)
    file(CREATE_LINK ${CMAKE_CURRENT_SOURCE_DIR}/ext/libstarshootg/mac/libstarshootg.dylib ${CMAKE_CURRENT_SOURCE_DIR}/ext/libstarshootg/libstarshootg.dylib SYMBOLIC)
    file(CREATE_LINK ${CMAKE_CURRENT_SOURCE_DIR}/ext/libnncam/mac/libnncam.dylib ${CMAKE_CURRENT_SOURCE_DIR}/ext/libnncam/libnncam.dylib SYMBOLIC)
    file(CREATE_LINK ${CMAKE_CURRENT_SOURCE_DIR}/ext/libomegonprocam/mac64/libomegonprocam.dylib ${CMAKE_CURRENT_SOURCE_DIR}/ext/libomegonprocam/libomegonprocam.dylib SYMBOLIC)
    file(CREATE_LINK ${CMAKE_CURRENT_SOURCE_DIR}/ext/libSVBCameraSDK/mac64/libSVBCameraSDK.dylib ${CMAKE_CURRENT_SOURCE_DIR}/ext/libSVBCameraSDK/libSVBCameraSDK.dylib SYMBOLIC)
    file(CREATE_LINK ${CMAKE_CURRENT_SOURCE_DIR}/ext/libmeadecam/mac/libmeadecam.dylib ${CMAKE_CURRENT_SOURCE_DIR}/ext/libmeadecam/libmeadecam.dylib SYMBOLIC)
    #OSX_FRAMEWORKS="-framework Carbon -framework VideoDecodeAcceleration -framework CoreVideo -framework IOKit $FW_CORE_MEDIA $FW_VID_TBOX"
    #FXLOAD_CFLAGS="-DFXLOAD_PATH=\\\"/MacOS/fxload\\\" -DFIRMWARE_QHY_PATH=\\\"/Resources/firmware/qhy\\\""
	#	SHLIBS_CFLAGS="-DSHLIB_PATH=\\\"/MacOS/\\\""
    #if test "x$use_system_libhidapi" == "xno"
    #then
    #  LIBHIDAPI_LIBS="\$(top_builddir)/ext/libhidapi/mac/libhidapi.la"
    #fi
    #APP_PATH_CFLAGS="-DUSE_APP_PATH=1"
    #DEFAULT_PATH_CFLAGS="-DUSE_HOME_DEFAULT=1"
    add_definitions(-DDYNLIB_EXT_DYLIB) 

ENDIF()


SET(ARMELAVAILABLE TRUE)
if(${arch} STREQUAL "arm5" OR ${arch} STREQUAL "arm6")
    set(ARMELAVAILABLE FALSE)
endif()
#if HAVE_LIBV4L2
#include "v4l2/V4L2oacam.h"
#endif
#if HAVE_LIBDC1394
#include "iidc/IIDCoacam.h"
#endif
#include "pwc/PWCoacam.h"
#if HAVE_LIBASI2
#include "zwo/ZWASI2oacam.h"
#endif
#include "qhy/QHYoacam.h"
#if HAVE_LIBUVC
#include "uvc/UVCoacam.h"
#endif
#include "sx/SX.h"
#include "sx/SXstate.h"
#include "sx/SXoacam.h"
#include "euvc/EUVC.h"
#include "euvc/EUVCstate.h"
#include "euvc/EUVCoacam.h"
#if HAVE_LIBUDEV || HAVE_LIBFTDI
#include "atik/atikSerialoacam.h"
#endif
#if HAVE_LIBFLYCAPTURE2
#include "flycap2/FC2oacam.h"
#endif
#if HAVE_LIBTOUPCAM
#include "toupcam/oacam.h"
#endif
#if HAVE_LIBMALLINCAM
#include "mallincam/oacam.h"
#endif
#if HAVE_LIBALTAIRCAM
#include "altair/oacam.h"
#endif
#if HAVE_LIBALTAIRCAM_LEGACY
#include "altair-legacy/oacam.h"
#endif
#if HAVE_LIBSTARSHOOTG
#include "starshootg/oacam.h"
#endif
#if HAVE_LIBNNCAM
#include "risingcam/oacam.h"
#endif
#if HAVE_LIBSPINNAKER
#include "spinnaker/Spinoacam.h"
#endif
#if HAVE_LIBARAVIS
#include "aravis/aravisoacam.h"
#endif
#if HAVE_LIBQHYCCD
#include "qhyccd/qhyccdoacam.h"
#endif
#if HAVE_LIBGPHOTO2
#include "gphoto2/GP2oacam.h"
#endif
#if HAVE_LIBOMEGONPROCAM
#include "omegonpro/oacam.h"
#endif
#if HAVE_LIBMEADECAM
#include "meadecam/oacam.h"
#endif
#if HAVE_PYLON
#include "pylon/oacam.h"
#endif
#if HAVE_LIBSVBCAMERASDK
#include "svbony/SVBoacam.h"

SET(HAVE_TOUPCAM ${ARMELAVAILABLE})
SET(HAVE_MALLINCAM ${ARMELAVAILABLE})
SET(HAVE_ALTAIRCAM ${ARMELAVAILABLE})
SET(HAVE_ALTAIRCAM_sLEGACY ${ARMELAVAILABLE})
SET(HAVE_STARSHOOTG ${ARMELAVAILABLE})
SET(HAVE_NNCAM ${ARMELAVAILABLE})
SET(HAVE_OMEGONPROCAM ${ARMELAVAILABLE})
SET(HAVE_QHYCCD ${ARMELAVAILABLE})

SET(HAVE_V4L2 FALSE)
#SET(HAVE_have_udev=no
#SET(HAVE_have_ftdi1=no
SET(HAVE_FLYCAPTURE2 FALSE)
SET(HAVE_SPINNAKER FALSE)
#SET(HAVE_have_dl=no

SET(INTERNAL_UVC FALSE)
SET(HAVE_LIBGPHOTO2 FALSE)
SET(SVNCAMERASDK FALSE)
SET(HAVE_MEADECAM FALSE)
SET(HAVE_LIBARAVIS FALSE)


if(HAVE_TOUPCAM AND NOT CHECKSYSTEMTOUPCAM) # TBD <- this needs to be done separately for most? then also modify in liboacam cmakelists
    SET(LIBTOUPCAM_CFLAGS "${CMAKE_CURRENT_SOURCE_DIR}/ext/libtoupcam/include")
    SET(LIBTOUPCAM_LIBS "")
    SET(HAVE_LIBTOUPCAM TRUE)

    SET(LIBALTAIRCAM_CFLAGS "${CMAKE_CURRENT_SOURCE_DIR}/ext/libaltaircam/include")
    SET(LIBALTAIRCAM_LIBS "")
    SET(HAVE_LIBALTAIRCAM TRUE)

    SET(LIBALTAIRCAM_LEGACY_CFLAGS "${CMAKE_CURRENT_SOURCE_DIR}/ext/libaltaircamlegacy/include")
    SET(LIBALTAIRCAM_LEGACY_LIBS "altaircamlegacy")
    SET(HAVE_LIBALTAIRCAM_LEGACY TRUE)

    SET(LIBSTARSHOOTG_CFLAGS "${CMAKE_CURRENT_SOURCE_DIR}/ext/libstarshootg/include")
    SET(LIBSTARSHOOTG_LIBS "")
    SET(HAVE_LIBSTARSHOOTG TRUE)

    SET(LIBNNCAM_CFLAGS "${CMAKE_CURRENT_SOURCE_DIR}/ext/libnncam/include")
    SET(LIBNNCAM_LIBS "")
    SET(HAVE_LIBNNCAM TRUE)
    
    SET(LIBOMEGONPROCAM_CFLAGS "${CMAKE_CURRENT_SOURCE_DIR}/ext/libomegonprocam/include")
    SET(LIBOMEGONPROCAM_LIBS "")
    SET(HAVE_OMEGONPROCAM TRUE)

    SET(LIBMEADECAM_CFLAGS "${CMAKE_CURRENT_SOURCE_DIR}/ext/libmeadecam/include")
    SET(LIBMEADECAM_LIBS "")
    SET(HAVE_LIBMEADECAM TRUE)

    SET(HAVE_LIBMALLINCAM TRUE)
endif()






#if test "x$use_system_libqhyccd" == "xno"
#then
#if test "x$have_qhyccd" != "xno"
#then
#LIBQHYCCD_CFLAGS="-I \$(top_srcdir)/ext/libqhyccd/include"
#LIBQHYCCD_LIBS=""
#AC_DEFINE([HAVE_LIBQHYCCD],[1],[Have qhyccd library support])
#fi
#fi


#if test "x$use_system_libsvbcamerasdk" == "xno"
#then
#if test "x$have_svbcamerasdk" != "xno"
#then
#LIBSVBCAMERASDK_CFLAGS="-I \$(top_srcdir)/ext/libSVBCameraSDK/include"
##LIBSVBCAMERASDK_LIBS="\$(top_builddir)/ext/libSVBCameraSDK/libSVBCameraSDK.a"
#LIBSVBCAMERASDK_LIBS=""
#AC_DEFINE([HAVE_LIBSVBCAMERASDK],[1],[Have SVBony library support])
##AC_DEFINE([HAVE_STATIC_LIBSVBCAMERASDK],[1],[Using static SVBony library])
#fi
#fi


## rm libwindi..? # rm liboademosaic liboafilterfwheel liboaimgproc?

# if not like above: ... and similar
# use_system_libtoupcam=no
# use_system_libmallincam=no
# if test "$checkSystemLibtoupcam" == "yes"
# then
#   if `$PKG_CONFIG --exists libtoupcam`; then
#     AC_MSG_NOTICE([Using system libtoupcam library])
#     flags=`$PKG_CONFIG --cflags-only-I libtoupcam`
# 		if test "$useisystemInclude" == "yes"; then
#       flags=`echo "$flags" | sed 's/^-I/-isystem/'`
#     fi
#     LIBTOUPCAM_CFLAGS="$flags"
#     # can't use shared libtoupcam if we're not using the system libusb
#     # because it will try to pull it in anyhow
#     if test "x$use_system_libusb" == "xyes"; then
#       LIBTOUPCAM_LDFLAGS="`$PKG_CONFIG --libs-only-L libtoupcam`"
#       LIBTOUPCAM_LIBS="`$PKG_CONFIG --libs-only-l libtoupcam`"
#     else
#       AC_MSG_WARN([libtoupcam not compatible with internal libusb.  No support for Touptek cameras.])
#     fi
#     use_system_libtoupcam=yes
#     AC_DEFINE([HAVE_LIBTOUPCAM],[1],[Have libtoupcam])
#   else
#     AC_CHECK_LIB([toupcam],[Toupcam_Open],[
#       LIBS="-ltoupcam $LIBS"
#       AC_DEFINE([HAVE_LIBTOUPCAM],[1],[Have libtoupcam])
#     ],[
#       AC_MSG_WARN([libtoupcam not found.  Dynamic support for Touptek cameras.])
#     ])
#   fi
# fi



#have_v4l2=no
#have_udev=no
# have_ftdi1=no
# have_flycapture2=no
# have_spinnaker=no
# have_dl=no
# have_meadecam=no
# have_libavformat=no
# have_libavutil=no
# have_libavcodec=no
# internal_uvc=no
# have_libgphoto2=no
# have_svbcamerasdk=no
# have_libaravis=no

# checkQtForPIC=no
# checkSystemFFMPEG=yes
# checkSystemLibusb=yes
# checkSystemDC1394=yes
# checkSystemLibuvc=no
# checkSystemLibhidapi=yes
# checkSystemLibasicamera=no
# checkSystemLibefwfilter=no
# checkSystemLibtoupcam=no
# checkSystemLibaltaircam=no
# checkSystemLibaltaircamlegacy=no
# checkSystemLibstarshootg=no
# checkSystemLibnncam=no
# checkSystemLibmallincam=no
# checkSystemLibomegonprocam=no
# checkSystemLibmeadecam=no
# checkSystemLibqhyccd=no
# checkSystemLibsvbcamerasdk=no
# useisystemInclude=no
# build_libusb=no
# zwoSupportedArch=yes
# case $host in
#   *-linux-*)
#     checkQtForPIC=yes
#     checkSystemDC1394=yes
#     checkSystemLibuvc=yes
#     checkSystemLibasicamera=yes
#     checkSystemLibefwfilter=yes
#     checkSystemLibtoupcam=$armelavailable
# 		checkSystemLibqhyccd=$armelavailable
# 		checkSystemLibaltaircam=$armelavailable
# 		checkSystemLibaltaircamlegacy=$armelavailable
# 		checkSystemLibmallincam=$armelavailable
#     checkSystemLibstarshootg=$armelavailable
#     checkSystemLibnncam=$armelavailable
#     checkSystemLibomegonprocam=$armelavailable
# 		#checkSystemLibmeadecam=$armelavailable
#     checkSystemLibmeadecam=no
# 		checkSystemLibsvbcamerasdk=yes
#     ;;
#   *-apple-*)
#     useisystemInclude=yes
#     build_libusb=yes
# 		have_svbcamerasdk=yes
#     ;;
# esac

INCLUDE (${CMAKE_ROOT}/Modules/CheckIncludeFile.cmake)
INCLUDE (CheckIncludeFileCXX)

SET(CMAKE_REQUIRED_INCLUDES ${INCLUDE_DIRECTORIES};/usr/local/include )

CHECK_INCLUDE_FILE( unistd.h HAVE_UNISTD_H )
CHECK_INCLUDE_FILE( errno.h HAVE_ERRNO_H ) 
#CHECK_INCLUDE_FILE( math.h HAVE_MATH_H )
CHECK_INCLUDE_FILE( limits.h HAVE_LIMITS_H )
#CHECK_INCLUDE_FILE( float.h HAVE_FLOAT_H )
CHECK_INCLUDE_FILE( malloc.h HAVE_MALLOC_H )
#CHECK_INCLUDE_FILE( stdint.h HAVE_STDINT_H )
#CHECK_INCLUDE_FILE( stdlib.h HAVE_STDLIB_H )
CHECK_INCLUDE_FILE( string.h HAVE_STRING_H )
CHECK_INCLUDE_FILE( strings.h HAVE_STRINGS_H )
CHECK_INCLUDE_FILE( sys/time.h HAVE_SYS_TIME_H )
#CHECK_INCLUDE_FILE( fitsio.h HAVE_FITSIO_H )
#CHECK_INCLUDE_FILE( cfitsio/fitsio.h HAVE_CFITSIO_FITSIO_H )
CHECK_INCLUDE_FILE( sys/sendfile.h HAVE_SYS_SENDFILE_H )
CHECK_INCLUDE_FILE( syslog.h HAVE_SYSLOG_H )
CHECK_INCLUDE_FILE( stdbool.h HAVE_STDBOOL_H )
CHECK_INCLUDE_FILE( hidapi/hidapi.h HAVE_HIDAPI_HIDAPI_H )
CHECK_INCLUDE_FILE( ftdi.h HAVE_FTDI_H )
CHECK_INCLUDE_FILE( libftdi/ftdi.h HAVE_LIBFTDI_FTDI_H )
CHECK_INCLUDE_FILE( libftdi1/ftdi.h HAVE_LIBFTDI1_FTDI_H )
CHECK_INCLUDE_FILE( sys/ioctl.h HAVE_SYS_IOCTL_H )
CHECK_INCLUDE_FILE( fcntl.h HAVE_FCNTL_H )
CHECK_INCLUDE_FILE( inttypes.h HAVE_INTTYPES_H )
CHECK_INCLUDE_FILE( memory.h HAVE_MEMORY_H )
CHECK_INCLUDE_FILE( dlfcn.h HAVE_DLFCN_H )

CHECK_INCLUDE_FILE( flycapture/C/FlyCapture2_C.h HAVE_FLYCAPTURE_C_FLYCAPTURE2_H )

#CHECK_INCLUDE_FILE_CXX( cerrno HAVE_CERRNO )
#CHECK_INCLUDE_FILE_CXX( cfloat HAVE_CFLOAT )
#CHECK_INCLUDE_FILE_CXX( climits HAVE_CLIMITS )
#CHECK_INCLUDE_FILE_CXX( cmath HAVE_CMATH )
#CHECK_INCLUDE_FILE_CXX( cstdint HAVE_STDINT )
#CHECK_INCLUDE_FILE_CXX( cstdlib HAVE_CSTDLIB )
#CHECK_INCLUDE_FILE_CXX( cstring HAVE_CSTRING )
#CHECK_INCLUDE_FILE_CXX( cstrings HAVE_CSTRINGS )

include(CheckSymbolExists)
check_symbol_exists(exp10 "math.h" HAVE_EXP10)
#check_symbol_exists(sqrt "math.h" HAVE_SQRT)
#check_symbol_exists(pow "math.h" HAVE_POW)
#check_symbol_exists(clock_gettime "time.h" HAVE_CLOCK_GETTIME)
check_symbol_exists(creat64 "fcntl.h" HAVE_CREAT64)
#check_symbol_exists(open64 "fcntl.h" HAVE_OPEN64)
check_symbol_exists(fopen64 "stdio.h" HAVE_FOPEN64)
#check_symbol_exists(freopen64 "stdio.h" HAVE_FREOPEN64)
check_symbol_exists(fseeki64 "stdio.h" HAVE_FSEEKI64)
check_symbol_exists(fseeko64 "stdio.h" HAVE_FSEEKO64)
check_symbol_exists(ftelli64 "stdio.h" HAVE_FTELLI64)
check_symbol_exists(ftello64 "stdio.h" HAVE_FTELLO64)
check_symbol_exists(ftdi_tcioflush "ftdi.h" HAVE_FTDI_TCIOFLUSH)
#check_symbol_exists(getcwd "unistd.h" HAVE_GETCWD)
check_symbol_exists(lseek64 "unistd.h" HAVE_LSEEK64)
#check_symbol_exists(gettimeofday "sys/time.h" HAVE_GETTIMEOFDAY)

CHECK_INCLUDE_FILE( flycapture/C/FlyCapture2_C.h HAVE_LIBFLYCAPTURE2)

include(CheckCXXSourceCompiles)
check_cxx_source_compiles("int main() { void* p = nullptr; }"
    HAVE_NULLPTR
    FAIL_REGEX "use of undeclared identifier 'nullptr'")

include_directories( /usr/local/include )
link_directories( /usr/local/lib )

INCLUDE (CheckLibraryExists)
SET(CMAKE_REQUIRED_INCLUDES ${LINK_DIRECTORIES};/usr/local/lib)
SET(CMAKE_REQUIRED_LIBRARIES ${CMAKE_REQUIRED_LIBRARIES} uvc)
CHECK_LIBRARY_EXISTS(uvc uvc_init /usr/local/lib HAVE_LIBUVC)

SET(CMAKE_REQUIRED_LIBRARIES ASICamera2)
CHECK_LIBRARY_EXISTS(ASICamera2 ASIGetNumOfConnectedCameras /usr/local/lib HAVE_LIBASI2) # TBD HOW TO BETTER SET LOCATION?

SET(CMAKE_REQUIRED_LIBRARIES ${CMAKE_REQUIRED_LIBRARIES} v4l2)
CHECK_LIBRARY_EXISTS(v4l2 v4l2_open /usr/local/lib HAVE_LIBV4L2)

IF(NOT HAVE_LIBASI2)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ext/libASICamera2/include )
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/ext/libASICamera2/mac )
SET( HAVE_LIBASI2 TRUE)
ENDIF()

IF(HAVE_LIBASI2)
    CHECK_SYMBOL_EXISTS(ASI_AUTO_MAX_EXP_MS "ASICamera2.h" HAVE_DECL_ASI_AUTO_MAX_EXP_MS)
    add_definitions(-DHAVE_LIBASI2=1 -DDYNLIB_EXTN_CFLAGS) # TBD ??
ENDIF()

IF(NOT HAVE_LIBUVC)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/ext/libuvc)
    SET(HAVE_LIBUVC TRUE)
ENDIF()

# ALSO FOR LIBUSB
# IF(NOT HAVE_UVC)
#     add_subdirectory(${CMAKE_SOURCE_DIR}/ext/libuvc)
#     SET(HAVE_UVC TRUE)
# ENDIF()

cmake_policy(SET CMP0075 NEW)

SET(CMAKE_REQUIRED_LIBRARIES ${CMAKE_REQUIRED_LIBRARIES} dc1394)
CHECK_LIBRARY_EXISTS(dc1394 dc1394_new /usr/local/lib HAVE_LIBDC1394)

SET(CMAKE_REQUIRED_LIBRARIES ${CMAKE_REQUIRED_LIBRARIES} gphoto2)
CHECK_LIBRARY_EXISTS(gp_context_new gpoto2 /usr/local/lib HAVE_GPHOTO2)

SET(CMAKE_REQUIRED_LIBRARIES "")


set(FXLOAD_PATH "\"/usr/local/bin/fxload\"")             # TBD
set(QHY_FIRMWARE_PATH "\"/usr/local/lib/firmware/qhy\"") # TBD


CHECK_LIBRARY_EXISTS(qhyccd ScanQHYCCD /usr/local/lib HAVE_QHYCCD)


include(CheckCSourceCompiles)

foreach(inline_keyword "inline" "__inline__" "__inline")
  if(NOT DEFINED C_INLINE)
    set(CMAKE_REQUIRED_DEFINITIONS_SAVE ${CMAKE_REQUIRED_DEFINITIONS})
    set(CMAKE_REQUIRED_DEFINITIONS ${CMAKE_REQUIRED_DEFINITIONS}
        "-Dinline=${inline_keyword}")
    check_c_source_compiles("
        typedef int foo_t;
        static inline foo_t static_foo() {return 0;}
        foo_t foo(){return 0;}
        int main(int argc, char *argv[]) {return 0;}"
      C_HAS_${inline_keyword})
    set(CMAKE_REQUIRED_DEFINITIONS ${CMAKE_REQUIRED_DEFINITIONS_SAVE})
    if(C_HAS_${inline_keyword})
      set(C_INLINE TRUE)
      set(INLINE_KEYWORD "${inline_keyword}")
    endif()
 endif()
endforeach()
if(NOT DEFINED C_INLINE)
  set(INLINE_KEYWORD)
endif()

SET( HAVE_CONFIG_H TRUE)
SET( HAVE_LIBDL TRUE)
SET( STDC_HEADERS TRUE )

add_definitions(-DHAVE_CONFIG_H=1)
add_definitions(-DHAVE_LIBDL=1)
configure_file(cm_config.h.in config.h)


include(GNUInstallDirs)

add_subdirectory(liboacam)
add_subdirectory(liboavideo)
add_subdirectory(liboautil)




# all kinds of logics to find libraries and to choose whether to use system or provided versions...

# also need to find and check the dependencies / and or build the ext stuff

# FXLOAD_CFLAGS="-DFXLOAD_PATH=\\\"\$(bindir)/fxload\\\" -DFIRMWARE_QHY_PATH=\\\"/lib/firmware/qhy\\\""
 #SHLIBS_CFLAGS=""


# apple:

# OSX_FRAMEWORKS="-framework Carbon -framework VideoDecodeAcceleration -framework CoreVideo -framework IOKit $FW_CORE_MEDIA $FW_VID_TBOX"
# FXLOAD_CFLAGS="-DFXLOAD_PATH=\\\"/MacOS/fxload\\\" -DFIRMWARE_QHY_PATH=\\\"/Resources/firmware/qhy\\\""
#    SHLIBS_CFLAGS="-DSHLIB_PATH=\\\"/MacOS/\\\""

# also for on off options etc need to see configure.ac