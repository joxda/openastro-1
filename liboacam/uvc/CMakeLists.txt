cmake_minimum_required(VERSION 3.11)
 
target_include_directories( oacam PRIVATE ${CMAKE_SOURCE_DIR}/ext/libuvc/include )


#-I/usr/local/include/libusb-1.0 -L/usr/local/lib -lusb-1.0
#
#  $(SHLIBS_CFLAGS) $(LIBASI2_CFLAGS) \
#  $(DYNLIB_EXTN_CFLAGS)
# -I/usr/local/Cellar/libuvc/0.0.6/include -I/usr/local/include/libusb-1.0 -L/usr/local/Cellar/libuvc/0.0.6/lib/ -L/usr/local/lib -luvc -lusb-1.0


target_sources(oacam PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/UVCoacam.c ${CMAKE_CURRENT_SOURCE_DIR}/UVCconnect.c ${CMAKE_CURRENT_SOURCE_DIR}/UVCgetState.c ${CMAKE_CURRENT_SOURCE_DIR}/UVCcontrol.c ${CMAKE_CURRENT_SOURCE_DIR}/UVCcontroller.c ${CMAKE_CURRENT_SOURCE_DIR}/UVCcallback.c ${CMAKE_CURRENT_SOURCE_DIR}/UVCExtnUnits.c ${CMAKE_CURRENT_SOURCE_DIR}/UVCdynloader.c ${CMAKE_CURRENT_SOURCE_DIR}/TISExtensionUnits.c )
