cmake_minimum_required(VERSION 3.11)
 
message("   Subdir pwc")
target_sources(oacam PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/PWCgetState.c ${CMAKE_CURRENT_SOURCE_DIR}/PWCconnect.c ${CMAKE_CURRENT_SOURCE_DIR}/PWCoacam.c )

