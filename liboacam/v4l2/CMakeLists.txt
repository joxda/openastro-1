cmake_minimum_required(VERSION 3.11)
 
message("   Subdir v4l2")


add_library(v4l2 OBJECT ${CMAKE_CURRENT_SOURCE_DIR}/V4L2oacam.c ${CMAKE_CURRENT_SOURCE_DIR}/V4L2connect.c ${CMAKE_CURRENT_SOURCE_DIR}/V4L2ioctl.c ${CMAKE_CURRENT_SOURCE_DIR}/V4L2cameras.c ${CMAKE_CURRENT_SOURCE_DIR}/V4L2getState.c ${CMAKE_CURRENT_SOURCE_DIR}/V4L2controller.c ${CMAKE_CURRENT_SOURCE_DIR}/V4L2callback.c ${CMAKE_CURRENT_SOURCE_DIR}/V4L2control.c ${CMAKE_CURRENT_SOURCE_DIR}/V4L2roi.c )
target_include_directories( v4l2 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../ext/libusb/include/ ${CMAKE_CURRENT_SOURCE_DIR}/../../include/ ${CMAKE_CURRENT_SOURCE_DIR}/../ ) # libusb? TBD
