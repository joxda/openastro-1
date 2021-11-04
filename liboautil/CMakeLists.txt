cmake_minimum_required(VERSION 3.11)

add_library(oautil STATIC llist.c exp10.c logging.c)
add_library(liboacam::oautil ALIAS oautil)

set_target_properties(oautil PROPERTIES OUTPUT_NAME "oautil")
set_target_properties(oautil PROPERTIES POSITION_INDEPENDENT_CODE TRUE)

target_include_directories( oautil PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include )
target_include_directories( oautil PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/../ )

install(TARGETS oautil LIBRARY)
