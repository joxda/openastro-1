cmake_minimum_required(VERSION 3.11)
 
message("   Subdir altair")

add_library(altair OBJECT ${CMAKE_CURRENT_SOURCE_DIR}/../touptek/oacam.c  ${CMAKE_CURRENT_SOURCE_DIR}/../touptek/connect.c ${CMAKE_CURRENT_SOURCE_DIR}/../touptek/callback.c ${CMAKE_CURRENT_SOURCE_DIR}/../touptek/control.c ${CMAKE_CURRENT_SOURCE_DIR}/../touptek/controller.c ${CMAKE_CURRENT_SOURCE_DIR}/../touptek/getState.c ${CMAKE_CURRENT_SOURCE_DIR}/../touptek/roi.c ${CMAKE_CURRENT_SOURCE_DIR}/../touptek/dynloader.c)

target_include_directories( altair PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../touptek/include ${LIBTOUPCAM_CFLAGS} ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories( altair PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../include/ ${CMAKE_CURRENT_SOURCE_DIR}/../../ext/libusb/include/ ${CMAKE_CURRENT_SOURCE_DIR}/../ ${CMAKE_CURRENT_SOURCE_DIR}/../../ext/libaltaircam/include/ ${CMAKE_CURRENT_SOURCE_DIR}/../../include/ ) # libusb? TBD
target_compile_definitions( altair PUBLIC HAVE_CONFIG_H HAVE_LIBDL)

target_link_libraries(altair PUBLIC dl ${LIBALTAIRCAM_LIBS} dl) # TBD libaltaircam
target_compile_definitions(altair PUBLIC ALTAIR)