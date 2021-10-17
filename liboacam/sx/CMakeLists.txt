cmake_minimum_required(VERSION 3.11)
 


  include_directories( ${CMAKE_SOURCE_DIR}/include )
  include_directories( ${CMAKE_SOURCE_DIR}/ext/libusb)
include_directories( ${CMAKE_SOURCE_DIR}/liboacam )
include_directories( ${CMAKE_SOURCE_DIR} )


add_library(sx SXoacam.c SXconnect.c SXcallback.c SXcontroller.c SXcontrol.c SXgetState.c SXroi.c )
link_libraries(sx ${CMAKE_DL_LIBS} ${USB1_LIBRARIES} )
