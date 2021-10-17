cmake_minimum_required(VERSION 3.11)
 

#find_package(libusb)

#-I/usr/local/include/libusb-1.0 -L/usr/local/lib -lusb-1.0
#
#  $(SHLIBS_CFLAGS) $(LIBASI2_CFLAGS) \
#  $(DYNLIB_EXTN_CFLAGS)
# -I/usr/local/Cellar/libuvc/0.0.6/include -I/usr/local/include/libusb-1.0 -L/usr/local/Cellar/libuvc/0.0.6/lib/ -L/usr/local/lib -luvc -lusb-1.0


add_library(pwc OBJECT PWCgetState.c PWCconnect.c PWCoacam.c )

link_libraries(pwc ${CMAKE_DL_LIBS} ${USB1_LIBRARIES} )
