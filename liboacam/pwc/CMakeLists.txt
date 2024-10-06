cmake_minimum_required(VERSION 3.11)
 
message("   Subdir pwc")
add_library(pwc OBJECT ${CMAKE_CURRENT_SOURCE_DIR}/PWCgetState.c ${CMAKE_CURRENT_SOURCE_DIR}/PWCconnect.c ${CMAKE_CURRENT_SOURCE_DIR}/PWCoacam.c )
target_include_directories(pwc PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../include/ ${CMAKE_CURRENT_SOURCE_DIR}/../ /usr/local/include/ ) 
if(BUILD_LIBUSB)
    target_include_directories( pwc PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../ext/libusb )
endif()