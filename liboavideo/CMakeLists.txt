cmake_minimum_required(VERSION 3.11)
 
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../include )

add_library(oavideo oavideo.c yuv.c fits.c formats.c to8Bit.c flip.c crop.c unpack.c alpha.c)

install(TARGETS oavideo LIBRARY)
