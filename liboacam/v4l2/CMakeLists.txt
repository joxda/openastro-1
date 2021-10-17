cmake_minimum_required(VERSION 3.11)
 
include_directories( ${CMAKE_SOURCE_DIR}/include )
include_directories( ${CMAKE_SOURCE_DIR}/liboacam )
include_directories( ${CMAKE_SOURCE_DIR} )

#  $(SHLIBS_CFLAGS) $(LIBASI2_CFLAGS) \
#  $(DYNLIB_EXTN_CFLAGS)

add_library(v4l2 OBJECT V4L2oacam.c V4L2connect.c V4L2ioctl.c V4L2cameras.c V4L2getState.c V4L2controller.c V4L2callback.c V4L2control.c V4L2roi.c )
link_libraries(v4l2 ${CMAKE_DL_LIBS})
