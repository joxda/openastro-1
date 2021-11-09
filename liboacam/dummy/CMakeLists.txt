cmake_minimum_required(VERSION 3.11)
 
message("   Subdir dummy")

add_library(dummy OBJECT ${CMAKE_CURRENT_SOURCE_DIR}/dummyoacam.c ${CMAKE_CURRENT_SOURCE_DIR}/dummyCallback.c ${CMAKE_CURRENT_SOURCE_DIR}/dummyroi.c ${CMAKE_CURRENT_SOURCE_DIR}/dummyController.c ${CMAKE_CURRENT_SOURCE_DIR}/dummyGetState.c ${CMAKE_CURRENT_SOURCE_DIR}/dummyControl.c ${CMAKE_CURRENT_SOURCE_DIR}/dummyconnect.c)
target_include_directories(dummy PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../include/ ${CMAKE_CURRENT_SOURCE_DIR}/../ )