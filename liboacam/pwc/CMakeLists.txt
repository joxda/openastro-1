cmake_minimum_required(VERSION 3.11)
 

#find_package(libusb)

#-I/usr/local/include/libusb-1.0 -L/usr/local/lib -lusb-1.0
#
#  $(SHLIBS_CFLAGS) $(LIBASI2_CFLAGS) \
#  $(DYNLIB_EXTN_CFLAGS)
# -I/usr/local/Cellar/libuvc/0.0.6/include -I/usr/local/include/libusb-1.0 -L/usr/local/Cellar/libuvc/0.0.6/lib/ -L/usr/local/lib -luvc -lusb-1.0

# TBD CHECK

target_sources(oacam PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/PWCgetState.c ${CMAKE_CURRENT_SOURCE_DIR}/PWCconnect.c ${CMAKE_CURRENT_SOURCE_DIR}/PWCoacam.c )

