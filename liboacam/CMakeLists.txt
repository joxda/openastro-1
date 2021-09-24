cmake_minimum_required(VERSION 3.11)

project(liboacam)
message( ${CMAKE_CURRENT_SOURCE_DIR}/../ext/libASICamera2/include  )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../include )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../ext/libusb )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../ext/libASICamera/include )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../ext/libtoupcam/include )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../ext/libqhyccd/include )

add_subdirectory(dummy)
add_subdirectory(zwo)

add_library(oacam control.c oacam.c unimplemented.c utils.c timer.c)

link_libraries(oacam dummy zwo  ${CMAKE_DL_LIBS})


