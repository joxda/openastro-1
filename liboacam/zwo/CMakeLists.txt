cmake_minimum_required(VERSION 3.11)
 
include_directories( ${CMAKE_SOURCE_DIR}/include )
include_directories( ${CMAKE_SOURCE_DIR} )
include_directories( ${CMAKE_SOURCE_DIR}/ext/libASICamera2/include )

#  $(SHLIBS_CFLAGS) $(LIBASI2_CFLAGS) \
#  $(DYNLIB_EXTN_CFLAGS)

add_library(zwo STATIC ZWASI2oacam.c ZWASI2connect.c ZWASI2controller.c ZWASI2getState.c ZWASI2control.c ZWASI2dynloader.c)


link_libraries(zwo ${CMAKE_DL_LIBS})
