cmake_minimum_required(VERSION 3.11)
 
include_directories( ${CMAKE_SOURCE_DIR}/../include )
include_directories( ${CMAKE_SOURCE_DIR} )

add_library(dummy OBJECT dummyoacam.c dummyCallback.c dummyroi.c dummyController.c dummyGetState.c dummyControl.c dummyconnect.c)


