cmake_minimum_required(VERSION 3.11)

message("   Subdir flycap")

set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS};-rdynamic)

add_library(flycap OBJECT ${CMAKE_CURRENT_SOURCE_DIR}/FC2oacam.c ${CMAKE_CURRENT_SOURCE_DIR}/FC2connect.c ${CMAKE_CURRENT_SOURCE_DIR}/FC2getState.c ${CMAKE_CURRENT_SOURCE_DIR}/FC2control.c ${CMAKE_CURRENT_SOURCE_DIR}/FC2controller.c ${CMAKE_CURRENT_SOURCE_DIR}/FC2callback.c ${CMAKE_CURRENT_SOURCE_DIR}/FC2roi.c ${CMAKE_CURRENT_SOURCE_DIR}/FC2dynloader.c)

target_include_directories(flycap PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../include/ ${CMAKE_CURRENT_SOURCE_DIR}/../ /usr/local/include/)
if(BUILD_LIBUSB)                                                                
    target_include_directories( flycap PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../ex\
t/libusb )                                                                      
endif()  