cmake_minimum_required(VERSION 3.11)
 

#cmake_policy(SET CMP0079 NEW)

#-I$(top_srcdir)/include \
#-I$(top_srcdir)/ext/libusb \
#-I$(top_srcdir)/liboacam \
#$(LIBUSB_CFLAGS) $(SHLIBS_CFLAGS) \
#$(LIBDC1394_CFLAGS) \
#$(DYNLIB_EXTN_CFLAGS)



message("   Subdir Iidc")
#target_sources(oacam PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/IIDCoacam.c ${CMAKE_CURRENT_SOURCE_DIR}/IIDCconnect.c ${CMAKE_CURRENT_SOURCE_DIR}/IIDCgetState.c ${CMAKE_CURRENT_SOURCE_DIR}/IIDCcontrol.c ${CMAKE_CURRENT_SOURCE_DIR}/IIDCcontroller.c ${CMAKE_CURRENT_SOURCE_DIR}/IIDCcallback.c ${CMAKE_CURRENT_SOURCE_DIR}/IIDCdynloader.c )
add_library(iidc OBJECT ${CMAKE_CURRENT_SOURCE_DIR}/IIDCoacam.c ${CMAKE_CURRENT_SOURCE_DIR}/IIDCconnect.c ${CMAKE_CURRENT_SOURCE_DIR}/IIDCgetState.c ${CMAKE_CURRENT_SOURCE_DIR}/IIDCcontrol.c ${CMAKE_CURRENT_SOURCE_DIR}/IIDCcontroller.c ${CMAKE_CURRENT_SOURCE_DIR}/IIDCcallback.c ${CMAKE_CURRENT_SOURCE_DIR}/IIDCdynloader.c )
target_include_directories(iidc PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../include/ ${CMAKE_CURRENT_SOURCE_DIR}/../ ${CMAKE_CURRENT_SOURCE_DIR}/../../ext/libusb ) # TBD that is add the include dir for libusb
target_compile_definitions(iidc PRIVATE HAVE_CONFIG_H=1 STDC_HEADERS=1 HAVE_LIBDL=1)
target_compile_options(iidc PUBLIC -DDYNLIB_EXT_DYLIB)

target_link_libraries(iidc PRIVATE dc1934 usb-1.0)

