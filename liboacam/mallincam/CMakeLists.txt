cmake_minimum_required(VERSION 3.11)
 
cmake_policy(SET CMP0079 NEW)

target_include_directories( oacam PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../touptek/include ${LIBMALLINCAM_CFLAGS} ${CMAKE_CURRENT_SOURCE_DIR})

message("   Subdir mallincam")

target_sources(oacam PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../touptek/oacam.c  ${CMAKE_CURRENT_SOURCE_DIR}/../touptek/connect.c ${CMAKE_CURRENT_SOURCE_DIR}/../touptek/callback.c ${CMAKE_CURRENT_SOURCE_DIR}/../touptek/control.c ${CMAKE_CURRENT_SOURCE_DIR}/../touptek/controller.c ${CMAKE_CURRENT_SOURCE_DIR}/../touptek/getState.c ${CMAKE_CURRENT_SOURCE_DIR}/../touptek/roi.c ${CMAKE_CURRENT_SOURCE_DIR}/../touptek/dynloader.c)
if(${LIBTOUPCAM_LIBS} NOT STREQUAL "")
target_link_libraries(oacam PRIVATE ${LIBTOUPCAM_LIBS})
endif()