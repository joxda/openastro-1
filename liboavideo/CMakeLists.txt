cmake_minimum_required(VERSION 3.11)

add_library(oavideo STATIC oavideo.c yuv.c fits.c formats.c to8Bit.c flip.c crop.c unpack.c alpha.c)
add_library(liboacam::oavideo ALIAS oavideo)

set_target_properties(oavideo PROPERTIES OUTPUT_NAME "oavideo")
set_target_properties(oavideo PROPERTIES POSITION_INDEPENDENT_CODE TRUE)

target_include_directories( oavideo PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include/ )
target_include_directories( oavideo PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/../ )

install(TARGETS oavideo LIBRARY)
