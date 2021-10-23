cmake_minimum_required(VERSION 3.11)

SET( CMAKE_C_STANDARD 99 )
project(liboacam)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

INCLUDE (${CMAKE_ROOT}/Modules/CheckIncludeFile.cmake)
INCLUDE (CheckIncludeFileCXX)
CHECK_INCLUDE_FILE( unistd.h HAVE_UNISTD_H )
CHECK_INCLUDE_FILE( errno.h HAVE_ERRNO_H ) 
CHECK_INCLUDE_FILE( math.h HAVE_MATH_H )
CHECK_INCLUDE_FILE( limits.h HAVE_LIMITS_H )
CHECK_INCLUDE_FILE( float.h HAVE_FLOAT_H )
CHECK_INCLUDE_FILE( malloc.h HAVE_MALLOC_H )
CHECK_INCLUDE_FILE( stdint.h HAVE_STDINT_H )
CHECK_INCLUDE_FILE( stdlib.h HAVE_STDLIB_H )
CHECK_INCLUDE_FILE( string.h HAVE_STRING_H )
CHECK_INCLUDE_FILE( strings.h HAVE_STRINGS_H )
CHECK_INCLUDE_FILE( sys/time.h HAVE_SYS_TIME_H )
CHECK_INCLUDE_FILE( fitsio.h HAVE_FITSIO_H )
CHECK_INCLUDE_FILE( cfitsio/fitsio.h HAVE_CFITSIO_FITSIO_H )
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

CHECK_INCLUDE_FILE( flycapture/C/FlyCapture2_C.h HAVE_FLYCAPTURE_C_FLYCAPTURE2_H )

CHECK_INCLUDE_FILE_CXX( cerrno HAVE_CERRNO )
CHECK_INCLUDE_FILE_CXX( cfloat HAVE_CFLOAT )
CHECK_INCLUDE_FILE_CXX( climits HAVE_CLIMITS )
CHECK_INCLUDE_FILE_CXX( cmath HAVE_CMATH )
CHECK_INCLUDE_FILE_CXX( cstdint HAVE_STDINT )
CHECK_INCLUDE_FILE_CXX( cstdlib HAVE_CSTDLIB )
CHECK_INCLUDE_FILE_CXX( cstring HAVE_CSTRING )
CHECK_INCLUDE_FILE_CXX( cstrings HAVE_CSTRINGS )

include(CheckSymbolExists)
check_symbol_exists(exp10 "math.h" HAVE_EXP10)
check_symbol_exists(clock_gettime "time.h" HAVE_CLOCK_GETTIME)
check_symbol_exists(creat64 "fcntl.h" HAVE_CREAT64)
check_symbol_exists(open64 "fcntl.h" HAVE_OPEN64)
check_symbol_exists(fopen64 "stdio.h" HAVE_FOPEN64)
check_symbol_exists(freopen64 "stdio.h" HAVE_FREOPEN64)
check_symbol_exists(fseeki64 "stdio.h" HAVE_FSEEKI64)
check_symbol_exists(fseeko64 "stdio.h" HAVE_FSEEKO64)
check_symbol_exists(ftelli64 "stdio.h" HAVE_FTELLI64)
check_symbol_exists(ftello64 "stdio.h" HAVE_FTELLO64)
check_symbol_exists(ftdi_tcioflush "ftdi.h" HAVE_FTDI_TCIOFLUSH)
check_symbol_exists(getcwd "unistd.h" HAVE_GETCWD)
check_symbol_exists(lseek64 "unistd.h" HAVE_LSEEK64)
check_symbol_exists(gettimeofday "sys/time.h" HAVE_GETTIMEOFDAY)

file(WRITE   ${CMAKE_BINARY_DIR}/CMakeFiles/test_nullptr.cpp "#include <stdio.h>\nint main()\n{\nvoid		*a = nullptr;\nprintf ( \"%p\n\", a );\n}")
try_compile(COMPILE_NULLPTR_SUCCEEDED ${CMAKE_BINARY_DIR}/CMakeFiles/compile_tests  ${CMAKE_BINARY_DIR}/CMakeFiles/test_nullptr.cpp )
if(COMPILE_NULLPTR_SUCCEEDED)
    SET(HAVE_NULLPTR True)
endif()

# Conditional on use of ASI SDK?

INCLUDE (CheckLibraryExists)
#Usage: CHECK_LIBRARY_EXISTS(library function location variable)
CHECK_LIBRARY_EXISTS(ASICamera2 ASIGetNumOfConnectedCameras "" HAVE_LIBASI2)
IF(HAVE_LIBASI2)
    CHECK_SYMBOL_EXISTS(ASI_AUTO_MAX_EXP_MS "ASICamera2.h" HAVE_DECL_ASI_AUTO_MAX_EXP_MS)
    add_definitions(-DHAVE_LIBASI2=1)
ENDIF()

CHECK_LIBRARY_EXISTS(ASICamera2 ScanQHYCCD "" HAVE_LIBASI2)



SET( HAVE_CONFIG_H TRUE)
SET( HAVE_LIBDL TRUE)
add_definitions(-DHAVE_CONFIG_H=1)
add_definitions(-DHAVE_LIBDL=1)
add_definitions(-DDYNLIB_EXT_DYLIB)
configure_file(${CMAKE_SOURCE_DIR}/cm_config.h.in ${CMAKE_BINARY_DIR}/config.h)

add_subdirectory(liboacam)
add_subdirectory(liboavideo)
add_subdirectory(liboautil)

include(${CMAKE_SOURCE_DIR}/cmake/TargetArch.cmake)
target_architecture(arch)
message(${arch})


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