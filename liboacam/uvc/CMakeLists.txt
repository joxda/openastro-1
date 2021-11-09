cmake_minimum_required(VERSION 3.11)
 
message("   Subdir uvc")


message(         ${CMAKE_CURRENT_SOURCE_DIR}/../../ext/libuvc/include/ )
add_library( uvc OBJECT ${CMAKE_CURRENT_SOURCE_DIR}/UVCoacam.c ${CMAKE_CURRENT_SOURCE_DIR}/UVCconnect.c ${CMAKE_CURRENT_SOURCE_DIR}/UVCgetState.c ${CMAKE_CURRENT_SOURCE_DIR}/UVCcontrol.c ${CMAKE_CURRENT_SOURCE_DIR}/UVCcontroller.c ${CMAKE_CURRENT_SOURCE_DIR}/UVCcallback.c ${CMAKE_CURRENT_SOURCE_DIR}/UVCExtnUnits.c ${CMAKE_CURRENT_SOURCE_DIR}/UVCdynloader.c ${CMAKE_CURRENT_SOURCE_DIR}/TISExtensionUnits.c )
target_include_directories( uvc PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../ext/libuvc/include/ ${CMAKE_CURRENT_SOURCE_DIR}/../../include/ ${CMAKE_CURRENT_SOURCE_DIR}/../ ${CMAKE_CURRENT_SOURCE_DIR}/../../ext/libuvc/include/ )
#target_link_libraries(uvc PUBLIC uvc) TBD

