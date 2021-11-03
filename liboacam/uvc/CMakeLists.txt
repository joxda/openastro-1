cmake_minimum_required(VERSION 3.11)
 
cmake_policy(SET CMP0079 NEW)

target_include_directories( oacam PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../ext/libuvc/include )

message("   Subdir uvc")

target_sources(oacam PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/UVCoacam.c ${CMAKE_CURRENT_SOURCE_DIR}/UVCconnect.c ${CMAKE_CURRENT_SOURCE_DIR}/UVCgetState.c ${CMAKE_CURRENT_SOURCE_DIR}/UVCcontrol.c ${CMAKE_CURRENT_SOURCE_DIR}/UVCcontroller.c ${CMAKE_CURRENT_SOURCE_DIR}/UVCcallback.c ${CMAKE_CURRENT_SOURCE_DIR}/UVCExtnUnits.c ${CMAKE_CURRENT_SOURCE_DIR}/UVCdynloader.c ${CMAKE_CURRENT_SOURCE_DIR}/TISExtensionUnits.c )
target_link_libraries(oacam PUBLIC uvc) 