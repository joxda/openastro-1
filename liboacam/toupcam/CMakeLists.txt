cmake_minimum_required(VERSION 3.11)
 


message("   Subdir toupcam")

add_library( toupcam OBJECT ${CMAKE_CURRENT_SOURCE_DIR}/../touptek/oacam.c  ${CMAKE_CURRENT_SOURCE_DIR}/../touptek/connect.c ${CMAKE_CURRENT_SOURCE_DIR}/../touptek/callback.c ${CMAKE_CURRENT_SOURCE_DIR}/../touptek/control.c ${CMAKE_CURRENT_SOURCE_DIR}/../touptek/controller.c ${CMAKE_CURRENT_SOURCE_DIR}/../touptek/getState.c ${CMAKE_CURRENT_SOURCE_DIR}/../touptek/roi.c ${CMAKE_CURRENT_SOURCE_DIR}/../touptek/dynloader.c)

target_include_directories( toupcam PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../touptek/include ${LIBTOUPCAM_CFLAGS} ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories( toupcam PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../ext/libusb/include/ ${CMAKE_CURRENT_SOURCE_DIR}/../../include/ ${CMAKE_CURRENT_SOURCE_DIR}/../  ) # libusb? TBD

target_link_libraries(toupcam PRIVATE ${LIBTOUPCAM_LIBS} ${CMAKE_DL_LIBS})

if(${LIBTOUPCAM_LIBS} NOT STREQUAL "")
target_compile_options(toupcam PRIVATE -Wno-visibility)
endif()