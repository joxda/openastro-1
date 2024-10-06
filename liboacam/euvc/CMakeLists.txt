cmake_minimum_required(VERSION 3.11)
 
#-I$(top_srcdir)/include \
#-I$(top_srcdir)/liboacam \
#$(LIBUSB_CFLAGS) \
#$(DYNLIB_EXTN_CFLAGS)
message("   Subdir euvc")

add_library(euvc OBJECT ${CMAKE_CURRENT_SOURCE_DIR}/EUVCoacam.c ${CMAKE_CURRENT_SOURCE_DIR}/EUVCconnect.c ${CMAKE_CURRENT_SOURCE_DIR}/EUVCcontrol.c ${CMAKE_CURRENT_SOURCE_DIR}/EUVCcallback.c ${CMAKE_CURRENT_SOURCE_DIR}/EUVCgetState.c ${CMAKE_CURRENT_SOURCE_DIR}/EUVCcontroller.c ${CMAKE_CURRENT_SOURCE_DIR}/EUVCusb.c ${CMAKE_CURRENT_SOURCE_DIR}/EUVCroi.c )
target_include_directories(euvc PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../include/ ${CMAKE_CURRENT_SOURCE_DIR}/../ /usr/local/include/) # TBD that is add the include dir for libusb
target_link_libraries(euvc PRIVATE usb-1.0 ${CMAKE_DL_LIBRARY})
#target_compile_definitions(euvc PRIVATE HAVE_CONFIG_H=1 STDC_HEADERS=1 HAVE_LIBDL=1)
target_compile_options(euvc PUBLIC -DDYNLIB_EXT_DYLIB)
message(${COMMON_COMPILE_OPTIONS})
#target_sources(oacam PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/EUVCoacam.c ${CMAKE_CURRENT_SOURCE_DIR}/EUVCconnect.c ${CMAKE_CURRENT_SOURCE_DIR}/EUVCcontrol.c ${CMAKE_CURRENT_SOURCE_DIR}/EUVCcallback.c ${CMAKE_CURRENT_SOURCE_DIR}/EUVCgetState.c ${CMAKE_CURRENT_SOURCE_DIR}/EUVCcontroller.c ${CMAKE_CURRENT_SOURCE_DIR}/EUVCusb.c ${CMAKE_CURRENT_SOURCE_DIR}/EUVCroi.c )
if(BUILD_LIBUSB)
    target_include_directories( euvc PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../ext/libusb )
endif()