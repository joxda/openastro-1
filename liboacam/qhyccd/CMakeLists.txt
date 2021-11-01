cmake_minimum_required(VERSION 3.11)
cmake_policy(SET CMP0079 NEW)

message ("   subdir qhyccd")
#target_include_directories( oacam PRIVATE ${CMAKE_SOURCE_DIR}/ext/libASICamera2/include )


#-DHAVE_CONFIG_H -I. -I../..  -I../../include -I../../ext/libusb -I../../liboacam -DFXLOAD_PATH=\"/MacOS/fxload\" -DFIRMWARE_QHY_PATH=\"/Resources/firmware/qhy\" -DDYNLIB_EXT_DYLIB 

#$(LIBUSB_CFLAGS) $(SHLIBS_CFLAGS) $(LIBQHYCCD_CFLAGS) \
#$(DYNLIB_EXTN_CFLAGS) $(FXLOAD_CFLAGS)

# TBD TBD TBD !!!

target_sources(oacam PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/qhyccdoacam.c ${CMAKE_CURRENT_SOURCE_DIR}/qhyccdconnect.c ${CMAKE_CURRENT_SOURCE_DIR}/qhyccdcontroller.c ${CMAKE_CURRENT_SOURCE_DIR}/qhyccdcontrol.c ${CMAKE_CURRENT_SOURCE_DIR}/qhyccdgetState.c ${CMAKE_CURRENT_SOURCE_DIR}/qhyccdroi.c ${CMAKE_CURRENT_SOURCE_DIR}/qhyccdcallback.c ${CMAKE_CURRENT_SOURCE_DIR}/qhyccdDynloader.c)

#target_link_directories(oacam PUBLIC ${CMAKE_SOURCE_DIR}/ext/libqhyccd/)
