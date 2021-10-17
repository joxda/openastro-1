cmake_minimum_required(VERSION 3.11)

project(liboacam)


SET( HAVE_UNISTD_H 1)

configure_file(config.h.in config.h)

add_subdirectory(liboacam)
add_subdirectory(liboavideo)
add_subdirectory(liboautil)



# Check config.h
# and oa_common.h
# for things that need to be checked and defined...
# also need to find and check the dependencies / and or build the ext stuff

# FXLOAD_CFLAGS="-DFXLOAD_PATH=\\\"\$(bindir)/fxload\\\" -DFIRMWARE_QHY_PATH=\\\"/lib/firmware/qhy\\\""
 #SHLIBS_CFLAGS=""


# apple:

# OSX_FRAMEWORKS="-framework Carbon -framework VideoDecodeAcceleration -framework CoreVideo -framework IOKit $FW_CORE_MEDIA $FW_VID_TBOX"
# FXLOAD_CFLAGS="-DFXLOAD_PATH=\\\"/MacOS/fxload\\\" -DFIRMWARE_QHY_PATH=\\\"/Resources/firmware/qhy\\\""
#    SHLIBS_CFLAGS="-DSHLIB_PATH=\\\"/MacOS/\\\""

# also for on off options etc need to see configure.ac