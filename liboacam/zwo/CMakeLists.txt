cmake_minimum_required(VERSION 3.11)
cmake_policy(SET CMP0079 NEW)

message ("   Subdir zwo")
target_include_directories( oacam PRIVATE ${CMAKE_SOURCE_DIR}/ext/libASICamera2/include )

#  $(SHLIBS_CFLAGS) $(LIBASI2_CFLAGS) \
#  $(DYNLIB_EXTN_CFLAGS)

target_sources(oacam PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/ZWASI2oacam.c ${CMAKE_CURRENT_SOURCE_DIR}/ZWASIcommon.c ${CMAKE_CURRENT_SOURCE_DIR}/ZWASIcommonControl.c ${CMAKE_CURRENT_SOURCE_DIR}/ZWASIroi.c ${CMAKE_CURRENT_SOURCE_DIR}/ZWASIcallback.c ${CMAKE_CURRENT_SOURCE_DIR}/ZWASI2connect.c ${CMAKE_CURRENT_SOURCE_DIR}/ZWASI2controller.c ${CMAKE_CURRENT_SOURCE_DIR}/ZWASI2getState.c ${CMAKE_CURRENT_SOURCE_DIR}/ZWASI2control.c ${CMAKE_CURRENT_SOURCE_DIR}/ZWASI2dynloader.c)
target_link_directories(oacam PUBLIC ${CMAKE_SOURCE_DIR}/ext/libASICamera2 ) # TBD EITHER HERE OR IN TOP CMAKE
target_link_libraries(oacam PUBLIC ASICamera2 ) #
