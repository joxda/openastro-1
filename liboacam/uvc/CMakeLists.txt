cmake_minimum_required(VERSION 3.11)
 
include_directories( ${CMAKE_SOURCE_DIR}/include )
include_directories( ${CMAKE_SOURCE_DIR}/liboacam )
include_directories( ${CMAKE_SOURCE_DIR} )
include_directories( ${CMAKE_SOURCE_DIR}/ext/libuvc/include )

find_package(libuvc)

#-I/usr/local/include/libusb-1.0 -L/usr/local/lib -lusb-1.0
#
#  $(SHLIBS_CFLAGS) $(LIBASI2_CFLAGS) \
#  $(DYNLIB_EXTN_CFLAGS)
# -I/usr/local/Cellar/libuvc/0.0.6/include -I/usr/local/include/libusb-1.0 -L/usr/local/Cellar/libuvc/0.0.6/lib/ -L/usr/local/lib -luvc -lusb-1.0


add_library(uvc OBJECT UVCoacam.c UVCconnect.c UVCgetState.c UVCcontrol.c UVCcontroller.c UVCcallback.c UVCExtnUnits.c UVCdynloader.c TISExtensionUnits.c )
link_libraries(uvc ${CMAKE_DL_LIBS} ${USB1_LIBRARIES} libuvc )
