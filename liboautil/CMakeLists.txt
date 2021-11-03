cmake_minimum_required(VERSION 3.11)

add_library(oautil llist.c exp10.c logging.c)
 
target_include_directories( oautil PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include )
target_include_directories( oautil PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/../ )

install(TARGETS oautil LIBRARY)
