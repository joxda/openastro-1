cmake_minimum_required(VERSION 3.11)

message("   Subdir sx")

add_library(sx OBJECT ${CMAKE_CURRENT_SOURCE_DIR}/SXoacam.c ${CMAKE_CURRENT_SOURCE_DIR}/SXconnect.c ${CMAKE_CURRENT_SOURCE_DIR}/SXcallback.c ${CMAKE_CURRENT_SOURCE_DIR}/SXcontroller.c ${CMAKE_CURRENT_SOURCE_DIR}/SXcontrol.c ${CMAKE_CURRENT_SOURCE_DIR}/SXgetState.c ${CMAKE_CURRENT_SOURCE_DIR}/SXroi.c )
target_include_directories(sx PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../include/ ${CMAKE_CURRENT_SOURCE_DIR}/../ /usr/local/include/ ) # TBD that is add the include dir for libusb)