cmake_minimum_required(VERSION 3.11)

SET( CMAKE_C_STANDARD 99 )
SET( CMAKE_CXX_STANDARD 11 )
cmake_policy(SET CMP0075 NEW)

project(liboacam)

# possibly put checks in separate file?


# need to check for dc1394 !
# also need to go through the different subdirs of liboacam to see what is needed... for what?
# In file included from /Users/jjjanz/openastro-1/liboacam/iidc/IIDCcontroller.c:39:
# /Users/jjjanz/openastro-1/liboacam/iidc/IIDCstate.h:31:10: fatal error: 'dc1394/dc1394.h' file not found
# #include <dc1394/dc1394.h>

# use internal alternatives?

# libraries: want to include vs available?

# $armelavailable logic?

# qhyccd special stuff see below


# TBD udev?

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

set(CMAKE_REQUIRED_INCLUDES /usr/local/include)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/TargetArch.cmake)
target_architecture(arch)
message(${arch})

IF(APPLE)
    SET(USB_OVERFLOW_HANGS TRUE)
    SET(HAVE_SVBCAMERASDK TRUE)
    SET(BUILD_LIBUSB TRUE)
ENDIF()


SET(ARMELAVAILABLE TRUE)
if(${arch} STREQUAL "arm5" OR ${arch} STREQUAL "arm6")
    set(ARMELAVAILABLE FALSE)
endif()


SET(HAVE_TOUPCAM ${ARMELAVAILABLE})
SET(HAVE_MALLINCAM ${ARMELAVAILABLE})
SET(HAVE_ALTAIRCAM ${ARMELAVAILABLE})
SET(HAVE_ALTAIRCAMLEGACY ${ARMELAVAILABLE})
SET(HAVE_STARSHOOTG ${ARMELAVAILABLE})
SET(HAVE_NNCAM ${ARMELAVAILABLE})
SET(HAVE_OMEGONPROCAM ${ARMELAVAILABLE})
SET(HAVE_QHYCCD ${ARMELAVAILABLE})


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
CHECK_INCLUDE_FILE( unistd.h HAVE_UNISTD_H )
CHECK_INCLUDE_FILE( errno.h HAVE_ERRNO_H ) 
#CHECK_INCLUDE_FILE( math.h HAVE_MATH_H )
CHECK_INCLUDE_FILE( limits.h HAVE_LIMITS_H )
#CHECK_INCLUDE_FILE( float.h HAVE_FLOAT_H )
CHECK_INCLUDE_FILE( malloc.h HAVE_MALLOC_H )
#CHECK_INCLUDE_FILE( stdint.h HAVE_STDINT_H )
CHECK_INCLUDE_FILE( stdlib.h HAVE_STDLIB_H )
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
check_symbol_exists(pow "math.h" HAVE_POW)
check_symbol_exists(clock_gettime "time.h" HAVE_CLOCK_GETTIME)
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
check_symbol_exists(gettimeofday "sys/time.h" HAVE_GETTIMEOFDAY)

CHECK_INCLUDE_FILE( flycapture/C/FlyCapture2_C.h HAVE_LIBFLYCAPTURE2)

include(CheckCXXSourceCompiles)
check_cxx_source_compiles("int main() { void* p = nullptr; }"
    HAVE_NULLPTR
    FAIL_REGEX "use of undeclared identifier 'nullptr'")

include_directories( /usr/local/include )
link_directories( /usr/local/lib )

INCLUDE (CheckLibraryExists)
SET(CMAKE_REQUIRED_INCLUDES /usr/local/lib)
SET(CMAKE_REQUIRED_LIBRARIES uvc)
CHECK_LIBRARY_EXISTS(uvc uvc_init /usr/local/lib HAVE_LIBUVC)

SET(CMAKE_REQUIRED_LIBRARIES ASICamera2)
CHECK_LIBRARY_EXISTS(ASICamera2 ASIGetNumOfConnectedCameras /usr/local/lib HAVE_LIBASI2) # TBD HOW TO BETTER SET LOCATION?

SET(CMAKE_REQUIRED_LIBRARIES v4l2)
CHECK_LIBRARY_EXISTS(v4l2 v4l2_open /usr/local/lib HAVE_LIBV4L2)

IF(NOT HAVE_LIBASI2)
include_directories(${CMAKE_SOURCE_DIR}/ext/libASICamera2/include )
link_directories(${CMAKE_SOURCE_DIR}/ext/libASICamera2/mac )
SET( HAVE_LIBASI2 TRUE)
ENDIF()

IF(HAVE_LIBASI2)
    CHECK_SYMBOL_EXISTS(ASI_AUTO_MAX_EXP_MS "ASICamera2.h" HAVE_DECL_ASI_AUTO_MAX_EXP_MS)
    add_definitions(-DHAVE_LIBASI2=1 -DDYNLIB_EXTN_CFLAGS) # TBD ??
ENDIF()

IF(NOT HAVE_LIBUVC)
    add_subdirectory(${CMAKE_SOURCE_DIR}/ext/libuvc)
    SET(HAVE_LIBUVC TRUE)
ENDIF()

# ALSO FOR LIBUSB
# IF(NOT HAVE_UVC)
#     add_subdirectory(${CMAKE_SOURCE_DIR}/ext/libuvc)
#     SET(HAVE_UVC TRUE)
# ENDIF()

cmake_policy(SET CMP0075 NEW)

SET(CMAKE_REQUIRED_LIBRARIES dc1394)
CHECK_LIBRARY_EXISTS(dc1394 dc1394_new /usr/local/lib HAVE_LIBDC1394)

SET(CMAKE_REQUIRED_LIBRARIES gphoto2)
CHECK_LIBRARY_EXISTS(gp_context_new gpoto2 /usr/local/lib HAVE_GPHOTO2)

SET(CMAKE_REQUIRED_LIBRARIES "")


set(FXLOAD_PATH "\"/usr/local/bin/fxload\"")             # TBD
set(QHY_FIRMWARE_PATH "\"/usr/local/lib/firmware/qhy\"") # TBD


CHECK_LIBRARY_EXISTS(qhyccd ScanQHYCCD /usr/local/lib HAVE_QHYCCD)

include_directories( ${CMAKE_BINARY_DIR} )

SET( HAVE_CONFIG_H TRUE)
SET( HAVE_LIBDL TRUE)
SET( STDC_HEADERS TRUE )

add_definitions(-DHAVE_CONFIG_H=1)
add_definitions(-DHAVE_LIBDL=1)
add_definitions(-DDYNLIB_EXT_DYLIB) # TBD?
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cm_config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h)

add_subdirectory(liboacam)
add_subdirectory(liboavideo)
add_subdirectory(liboautil)


# LINK FILES...

#armelavailable=yes
#case $host in
#  *-apple-*|i?86-*-*|x86_64-*-*|armv[78]l-*-*|aarch64-*-*)
#		;;
#  armv[56]l-*-*)
#		armelavailable=no
#		;;
#esac

# have_v4l2=no
# have_udev=no
# have_ftdi1=no
# have_flycapture2=no
# have_spinnaker=no
# have_dl=no
# have_toupcam=$armelavailable
# have_mallincam=$armelavailable
# have_altaircam=$armelavailable
# have_altaircamlegacy=$armelavailable
# have_starshootg=$armelavailable
# have_nncam=$armelavailable
# have_omegonprocam=$armelavailable
# #have_meadecam=$armelavailable
# have_meadecam=no
# have_qhyccd=$armelavailable
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


# all kinds of logics to find libraries and to choose whether to use system or provided versions...




# Check config.h
# and oa_common.h
# for things that need to be checked and defined...
# also need to find and check the dependencies / and or build the ext stuff

# FXLOAD_CFLAGS="-DFXLOAD_PATH=\\\"\$(bindir)/fxload\\\" -DFIRMWARE_QHY_PATH=\\\"/lib/firmware/qhy\\\""
 #SHLIBS_CFLAGS=""


# apple:

# OSX_FRAMEWORKS="-framework Carbon -framework VideoDecodeAcceleration -framework CoreVideo -framework IOKit $FW_CORE_MEDIA $FW_VID_TBOX"
# FXLOAD_CFLAGS="-DFXLOAD_PATH=\\\"/MacOS/fxload\\\" -DFIRMWARE_QHY_PATH=\\\"/Resources/firmware/qhy\\\""
#    SHLIBS_CFLAGS="-DSHLIB_PATH=\\\"/MacOS/\\\""

# also for on off options etc need to see configure.ac