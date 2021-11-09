cmake_minimum_required(VERSION 3.11)

message ("   Subdir qhyccd")


#-DHAVE_CONFIG_H -I. -I../..  -I../../include -I../../ext/libusb -I../../liboacam -DFXLOAD_PATH=\"/MacOS/fxload\" -DFIRMWARE_QHY_PATH=\"/Resources/firmware/qhy\" -DDYNLIB_EXT_DYLIB 

#$(LIBUSB_CFLAGS) $(SHLIBS_CFLAGS) $(LIBQHYCCD_CFLAGS) \
#$(DYNLIB_EXTN_CFLAGS) $(FXLOAD_CFLAGS)

# TBD TBD TBD !!!
add_library(qhyccd OBJECT ${CMAKE_CURRENT_SOURCE_DIR}/qhyccdoacam.c ${CMAKE_CURRENT_SOURCE_DIR}/qhyccdconnect.c ${CMAKE_CURRENT_SOURCE_DIR}/qhyccdcontroller.c ${CMAKE_CURRENT_SOURCE_DIR}/qhyccdcontrol.c ${CMAKE_CURRENT_SOURCE_DIR}/qhyccdgetState.c ${CMAKE_CURRENT_SOURCE_DIR}/qhyccdroi.c ${CMAKE_CURRENT_SOURCE_DIR}/qhyccdcallback.c ${CMAKE_CURRENT_SOURCE_DIR}/qhyccdDynloader.c)
target_compile_options(qhyccd PRIVATE -Wno-visibility)
target_include_directories( qhyccd PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../include/  ${CMAKE_CURRENT_SOURCE_DIR}/../../ext/libqhyccd/include ${CMAKE_CURRENT_SOURCE_DIR}/../ )
target_compile_definitions(qhyccd PRIVATE FXLOAD_PATH=${FXLOAD_PATH} FIRMWARE_QHY_PATH=${QHY_FIRMWARE_PATH})

#target_link_directories(oacam PUBLIC ${CMAKE_SOURCE_DIR}/ext/libqhyccd/)
