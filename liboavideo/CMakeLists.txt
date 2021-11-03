cmake_minimum_required(VERSION 3.11)

add_library(oavideo oavideo.c yuv.c fits.c formats.c to8Bit.c flip.c crop.c unpack.c alpha.c)

target_include_directories( oavideo PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include/ )
target_include_directories( oavideo PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/../ )

install(TARGETS oavideo LIBRARY)
