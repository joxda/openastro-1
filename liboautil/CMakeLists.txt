cmake_minimum_required(VERSION 3.11)
 
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../include )

add_library(oautil llist.c exp10.c logging.c)

install(TARGETS oautil LIBRARY)
