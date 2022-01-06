cmake_minimum_required(VERSION 3.11)

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


message("CHECK THIS OUT ${CMAKE_CURRENT_BINARY_DIR}/ }")
add_library(oacam STATIC control.c oacam.c unimplemented.c utils.c timer.c)
add_library(liboacam::oacam ALIAS oacam)

set_target_properties(oacam PROPERTIES OUTPUT_NAME "oacam")
set_target_properties(oacam PROPERTIES POSITION_INDEPENDENT_CODE TRUE)

set_property(TARGET oacam PROPERTY C_STANDARD 99)     

target_include_directories( oacam PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/../ ${CMAKE_CURRENT_SOURCE_DIR}/../include )

target_include_directories( oacam PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} )
target_include_directories( oacam PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include )
if(BUILD_LIBUSB)
    target_include_directories( oacam PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../ext/libusb )
endif()
target_include_directories( oacam PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../ext/libASICamera/include )
target_include_directories( oacam PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../ext/libtoupcam/include )
target_include_directories( oacam PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../ext/libqhyccd/include )
target_include_directories( oacam PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/../ )
target_include_directories( oacam PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/../include )

target_link_libraries(oacam PUBLIC dl)
message(" THISTHISTHIS                  ${CMAKE_DL_LIBS}")
add_subdirectory(euvc)
target_link_libraries(oacam PUBLIC $<TARGET_OBJECTS:euvc>  )

add_subdirectory(pwc)
target_link_libraries(oacam PUBLIC  $<TARGET_OBJECTS:pwc>  )

add_subdirectory(qhy)
target_link_libraries(oacam  PUBLIC  $<TARGET_OBJECTS:qhy>  )

add_subdirectory(sx)
target_link_libraries(oacam PUBLIC  $<TARGET_OBJECTS:sx>  )

add_subdirectory(dummy)
target_link_libraries(oacam  PUBLIC  $<TARGET_OBJECTS:dummy>  )

if(HAVE_LIBFLYCAPTURE2)
    add_subdirectory(flycap2)
    target_link_libraries(oacam  PUBLIC  $<TARGET_OBJECTS:flycap>  )
endif()

if(HAVE_LIBDC1394)
  add_subdirectory(iidc)
  target_link_libraries(oacam  PUBLIC  $<TARGET_OBJECTS:iidc>  )
endif()

#if(HAVE_LIBASI2)    
   add_subdirectory(zwo)
   target_link_libraries(oacam  PUBLIC  $<TARGET_OBJECTS:zwo>  )
   #target_link_libraries(oacam PRIVATE ASICamera2 ) #


#endif()

#if(HAVE_LIBUVC)
   add_subdirectory(uvc)
    target_include_directories(oacam PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../ext/libuvc/include/ )
    target_link_libraries(oacam  PRIVATE $<TARGET_OBJECTS:uvc>  )
#endif()

if(HAVE_GPHOTO2)
    add_subdirectory(gphoto2)
    target_link_libraries(oacam PUBLIC  $<TARGET_OBJECTS:gphoto2>  )
endif()

if(HAVE_QHYCCD)
    add_subdirectory(qhyccd)
    target_link_libraries(oacam PUBLIC $<TARGET_OBJECTS:qhyccd>  )
endif()

if(HAVE_LIBV4L2)
    if(${arch} STREQUAL "arm5" OR ${arch} STREQUAL "arm6"  OR ${arch} STREQUAL "arm7" )
        SET(V4L2_MEMORY_RESTRICTED TRUE)
    endif()
   add_subdirectory(v4l2)
   target_link_libraries(oacam PUBLIC  $<TARGET_OBJECTS:v4l2>  )
endif()

if(HAVE_LIBTOUPCAM) # TBD ONE BY ONE
    add_subdirectory(toupcam)
    target_link_libraries(oacam PUBLIC $<TARGET_OBJECTS:toupcam> )
endif(HAVE_LIBTOUPCAM)
if(HAVE_LIBSTARSHOOTG)
    add_subdirectory(starshootg)
    target_link_libraries(oacam PUBLIC $<TARGET_OBJECTS:starshootg> )
endif()
if(HAVE_LIBRISINGCAM)
    add_subdirectory(risingcam)
    target_link_libraries(oacam PUBLIC $<TARGET_OBJECTS:risingcam> )
endif()
if(HAVE_LIBOMEGONPROCAM)
    add_subdirectory(omegonpro)
    target_link_libraries(oacam PUBLIC $<TARGET_OBJECTS:omegonpro> )
endif()
#if(HAVE_LIBMEADECAM)
#    add_subdirectory(meadecam)
#    target_link_libraries(oacam PUBLIC $<TARGET_OBJECTS:meadecam> )
#endif()
if(HAVE_LIBMALLINCAM)
    add_subdirectory(mallincam)
    target_link_libraries(oacam PUBLIC $<TARGET_OBJECTS:mallincam> )
endif()
if(HAVE_LIBALTAIRCAM_LEGACY)
    add_subdirectory(altair-legacy)
    target_link_libraries(oacam PUBLIC $<TARGET_OBJECTS:altair-legacy> )
endif()
if(HAVE_LIBALTAIRCAM)
    add_subdirectory(altair)
    target_link_libraries(oacam PUBLIC $<TARGET_OBJECTS:altair> )
endif()

target_link_libraries(oacam PUBLIC dl)



target_link_directories(oacam PUBLIC "/usr/local/lib/")
target_include_directories(oacam PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include> 
$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}> )
target_include_directories(oacam PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}> 
$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}> )

file(GLOB_RECURSE INCLUDE_FILES "../include/*.h*") 
set(INCLUDE_FILES ${INCLUDE_FILES};${CMAKE_CURRENT_BINARY_DIR}/../config.h)
if (APPLE)
set_target_properties(oacam PROPERTIES PUBLIC_HEADER "${INCLUDE_FILES}" LINK_FLAGS "-Wl,-all_load")
else ()
set_target_properties(oacam PROPERTIES PUBLIC_HEADER "${INCLUDE_FILES}" LINK_FLAGS "-Wl,--whole-archive")
endif()
# DO SUMMARY !!

install(TARGETS oacam EXPORT oacam-targets LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

#install(FILES ${CMAKE_CURRENT_BINARY_DIR}/../config.h DESTINATION etc/solshare_stats COMPONENT config)

install(EXPORT oacam-targets DESTINATION ${CMAKE_INSTALL_BINDIR}/cmake/liboacam NAMESPACE liboacam:: DESTINATION "liboacamConfigTargets.cmake")