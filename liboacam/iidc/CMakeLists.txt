cmake_minimum_required(VERSION 3.11)
 
include_directories( ${CMAKE_SOURCE_DIR}/include )
include_directories( ${CMAKE_SOURCE_DIR}/ext/libusb )
include_directories( ${CMAKE_SOURCE_DIR}/ext/libusb )
include_directories( ${CMAKE_SOURCE_DIR}/liboacam )
include_directories( ${CMAKE_SOURCE_DIR} )


#find_package(libusb)

#$(SHLIBS_CFLAGS) \
#$(LIBDC1394_CFLAGS) \

add_library(iidc OBJECT IIDCoacam.c IIDCconnect.c IIDCgetState.c IIDCcontrol.c IIDCcontroller.c IIDCcallback.c IIDCdynloader.c )
link_libraries(iidc dc1394 ${CMAKE_DL_LIBS} ${USB1_LIBRARIES} )
target_include_directories( iidc PRIVATE /usr/local/include/ )
