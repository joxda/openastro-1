cmake_minimum_required(VERSION 3.11)
subdir("   Subdir gphoto2")
add_library(gphoto2 OBJECT ${CMAKE_CURRENT_SOURCE_DIR}/GP2oacam.c ${CMAKE_CURRENT_SOURCE_DIR}/GP2dynloader.c ${CMAKE_CURRENT_SOURCE_DIR}/GP2connect.c ${CMAKE_CURRENT_SOURCE_DIR}/GP2common.c ${CMAKE_CURRENT_SOURCE_DIR}/GP2getState.c ${CMAKE_CURRENT_SOURCE_DIR}/GP2control.c ${CMAKE_CURRENT_SOURCE_DIR}/GP2controller.c ${CMAKE_CURRENT_SOURCE_DIR}/GP2callback.c)

# TBD  $(SHLIBS_CFLAGS) $(LIBGPHOTO2_CFLAGS) $(DYNLIB_EXTN_CFLAGS)
target_include_directories(gphoto2 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../include/ ${CMAKE_CURRENT_SOURCE_DIR}/../ /usr/local/include/) # TBD that is add the include dir for libusb
