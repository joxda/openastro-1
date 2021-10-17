cmake_minimum_required(VERSION 3.11)

#  $(FXLOAD_CFLAGS) \
 
# also FXLOAD_PATH ??
# FIRMWARE_QHY_PATH ??

  include_directories( ${CMAKE_SOURCE_DIR}/include )
  include_directories( ${CMAKE_SOURCE_DIR}/ext/libusb )
include_directories( ${CMAKE_SOURCE_DIR}/liboacam )
include_directories( ${CMAKE_SOURCE_DIR} )

#find_package(libusb)
# SET TO SOMETHING REASONABLE
add_definitions(-DFXLOAD_PATH="/usr/local/bin/fxload" -DFIRMWARE_QHY_PATH="/usr/local/lib/firmware/qhy")

add_library(qhy OBJECT QHYoacam.c QHYconnect.c QHYfirmware.c QHYcontrol.c QHYcallback.c QHYgetState.c QHYusb.c QHY5.c QHY5controller.c QHY5II.c QHY5IIcontroller.c QHY5LII.c QHY5LIIcontroller.c QHY6.c QHY6controller.c IMG132E.c IMG132Econtroller.c )
link_libraries(qhy ${CMAKE_DL_LIBS} ${USB1_LIBRARIES} )

