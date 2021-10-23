cmake_minimum_required(VERSION 3.11)
 
include_directories( ${CMAKE_SOURCE_DIR}/include )
include_directories( ${CMAKE_BINARY_DIR}/ )

add_library(oautil llist.c exp10.c logging.c)

install(TARGETS oautil LIBRARY)
