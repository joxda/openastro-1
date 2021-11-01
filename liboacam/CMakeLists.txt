cmake_minimum_required(VERSION 3.11)

project(liboacam)
message( ${CMAKE_CURRENT_SOURCE_DIR}/../ext/libASICamera2/include  )

#  $(LIBUSB_CFLAGS) $(LIBUVC_CFLAGS) \
#  $(LIBALTAIRCAM_CFLAGS) $(LIBALTAIRCAM_LEGACY_CFLAGS) $(LIBTOUPCAM_CFLAGS) \
#	$(LIBQHYCCD_CFLAGS) $(PYLON_CFLAGS) $(LIBMEADECAM_CFLAGS) \
#  $(DYNLIB_EXTN_CFLAGS)


# lib_LTLIBRARIES = liboacam.la
# 
# if LIBASI2_COND
# ZWODIR= zwo
# ZWOLIB= /libzwo.la
# endif
# 
# if LIBV4L2_COND
# V4L2DIR= v4l2
# V4L2LIB= /libvideo4linux.la
# endif
# 
# if LIBFLYCAPTURE2_COND
# FC2DIR= flycap2
# FC2LIB= /libflycap2.la
# endif
# 
# if LIBSPINNAKER_COND
# SPINDIR= spinnaker
# SPINLIB= /libspinnaker.la
# endif
# 
# if LIBARAVIS_COND
# ARAVISDIR= aravis
# ARAVISLIB= /libaravis.la
# endif
# 
# if ATIK_COND
# ATIKDIR= atik
# ATIKLIB= /libatik.la
# endif
# 
# if LIBTOUPCAM_COND
# TOUPCAMDIR = toupcam
# TOUPCAMLIB = /libtoupcam.la
# endif
# 
# if LIBMALLINCAM_COND
# MALLINCAMDIR= mallincam
# MALLINCAMLIB= /libmallincam.la
# endif
# 
# if LIBALTAIRCAM_COND
# ALTAIRDIR= altair
# ALTAIRLIB= /libaltaircam.la
# endif
# 
# if LIBSTARSHOOTG_COND
# STARSHOOTGDIR= starshootg
# STARSHOOTGLIB= /libstarshootg.la
# endif
# 
# if LIBNNCAM_COND
# RISINGCAMDIR= risingcam
# RISINGCAMLIB= /librisingcam.la
# endif
# 
# if LIBALTAIRCAM_LEGACY_COND
# ALTAIRLEGACYDIR= altair-legacy
# ALTAIRLEGACYLIB= /libaltairlegacy.la
# endif
# 
# if LIBQHYCCD_COND
# QHYCCDDIR = qhyccd
# QHYCCDLIB = /libqhyccd.la
# endif
# 
# if LIBGPHOTO2_COND
# GPHOTO2DIR = gphoto2
# GPHOTO2LIB = /libgphoto2.la
# endif
# 
# if LIBOMEGONPROCAM_COND
# OMEGONPROCAMDIR = omegonpro
# OMEGONPROCAMLIB = /libomegoncam.la
# endif
# 
# if PYLON_COND
# PYLONDIR = pylon
# PYLONLIB = /libpylon.la
# endif
# 
# if LIBSVBCAMERASDK_COND
# SVBONYDIR = svbony
# SVBONYLIB = /libsvbony.la
# endif
# 
# if LIBMEADECAM_COND
# MEADECAMDIR = meadecam
# MEADECAMLIB = /libmeadecam.la
# endif


# SUBDIRS	= euvc iidc pwc qhy sx uvc dummy $(ALTAIRDIR) $(ATIKDIR) \
#	$(MALLINCAMDIR) $(FC2DIR) $(SPINDIR) $(TOUPCAMDIR) $(V4L2DIR) $(ZWODIR) \
#	$(ALTAIRLEGACYDIR) $(QHYCCDDIR) $(GPHOTO2DIR) $(STARSHOOTGDIR) \
#	$(RISINGCAMDIR) $(OMEGONPROCAMDIR) $(PYLONDIR) $(SVBONYDIR) $(ARAVISDIR) \
#	$(MEADECAMDIR) . demo


# liboacam_la_LIBADD = euvc/libeuvc.la iidc/libiidc.la pwc/libpwc.la \
#  qhy/libqhy.la sx/libsx.la uvc/libuvc.la dummy/libdummy.la $(ALTAIRLIB) \
#	$(ATIKLIB) $(MALLINCAMLIB) $(FC2LIB) $(SPINLIB) $(TOUPCAMLIB) $(V4L2LIB) \
#	$(ZWOLIB) $(ALTAIRLEGACYLIB) $(QHYCCDLIB) $(GPHOTO2LIB) $(STARSHOOTGLIB) \
#	$(RISINGCAMLIB) $(OMEGONPROCAMLIB) $(PYLONLIB) $(SVBONYLIB) $(ARAVISLIB) \
#	$(MEADECAMLIB)



include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../include )
if(BUILD_LIBUSB)
    include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../ext/libusb )
endif()
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../ext/libASICamera/include )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../ext/libtoupcam/include )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../ext/libqhyccd/include )


add_library(oacam control.c oacam.c unimplemented.c utils.c timer.c)
set_property(TARGET oacam PROPERTY C_STANDARD 99)     

add_subdirectory(euvc)
add_subdirectory(pwc)
add_subdirectory(qhy)
add_subdirectory(sx)
add_subdirectory(dummy)


link_libraries(oacam STATIC PUBLIC '''$<TARGET_OBJECTS:euvc>''' $<TARGET_OBJECTS:iidc> $<TARGET_OBJECTS:pwc> $<TARGET_OBJECTS:qhy> $<TARGET_OBJECTS:sx> $<TARGET_OBJECTS:uvc> $<TARGET_OBJECTS:dummy> $<TARGET_OBJECTS:v4l2> $<TARGET_OBJECTS:zwo> ${CMAKE_DL_LIBS} ${USB1_LIBRARIES} )

if(HAVE_LIBFLYCAPTURE2)
    add_subdirectory(flycap2)
endif()

if(HAVE_LIBDC1394)
  add_subdirectory(iidc)
endif()

if(HAVE_LIBASI2)    
   add_subdirectory(zwo)
endif()

if(HAVE_LIBUVC)
    add_subdirectory(uvc)
endif()

if(HAVE_GPHOTO2)
    add_subdirectory(gphoto2)
endif()

if(HAVE_QHYCCD)
    add_subdirectory(qhyccd)
endif()

if(HAVE_LIBV4L2)
   add_subdirectory(v4l2)
   if(${arch} STREQUAL "arm5" OR ${arch} STREQUAL "arm6"  OR ${arch} STREQUAL "arm7" )
    SET(V4L2_MEMORY_RESTRICTED TRUE)
   endif()
endif()

target_include_directories(oacam PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)                                                          
file(GLOB_RECURSE INCLUDE_FILES "../include/*.h*")                                                                                                 
set_target_properties(                                                                                                                             oacam PROPERTIES
    PUBLIC_HEADER "${INCLUDE_FILES}"                                                                                                            
)          

# DO SUMMARY !!

install(TARGETS oacam LIBRARY PUBLIC_HEADER DESTINATION include)

