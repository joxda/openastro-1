cmake_minimum_required(VERSION 3.11)
 

cmake_policy(SET CMP0079 NEW)

message("   Subdir Iidc")
target_sources(oacam PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/IIDCoacam.c ${CMAKE_CURRENT_SOURCE_DIR}/IIDCconnect.c ${CMAKE_CURRENT_SOURCE_DIR}/IIDCgetState.c ${CMAKE_CURRENT_SOURCE_DIR}/IIDCcontrol.c ${CMAKE_CURRENT_SOURCE_DIR}/IIDCcontroller.c ${CMAKE_CURRENT_SOURCE_DIR}/IIDCcallback.c ${CMAKE_CURRENT_SOURCE_DIR}/IIDCdynloader.c )

target_link_libraries(oacam PRIVATE dc1934)