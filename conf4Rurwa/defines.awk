BEGIN {
D["PACKAGE_NAME"]=" \"openastro\""
D["PACKAGE_TARNAME"]=" \"openastro\""
D["PACKAGE_VERSION"]=" \"1.9.0\""
D["PACKAGE_STRING"]=" \"openastro 1.9.0\""
D["PACKAGE_BUGREPORT"]=" \"james@openastroproject.org\""
D["PACKAGE_URL"]=" \"\""
D["PACKAGE"]=" \"openastro\""
D["VERSION"]=" \"1.9.0\""
D["STDC_HEADERS"]=" 1"
D["HAVE_SYS_TYPES_H"]=" 1"
D["HAVE_SYS_STAT_H"]=" 1"
D["HAVE_STDLIB_H"]=" 1"
D["HAVE_STRING_H"]=" 1"
D["HAVE_MEMORY_H"]=" 1"
D["HAVE_STRINGS_H"]=" 1"
D["HAVE_INTTYPES_H"]=" 1"
D["HAVE_STDINT_H"]=" 1"
D["HAVE_UNISTD_H"]=" 1"
D["HAVE_DLFCN_H"]=" 1"
D["LT_OBJDIR"]=" \".libs/\""
D["HAVE_LIBTIFF"]=" 1"
D["HAVE_LIBPNG"]=" 1"
D["HAVE_LIBJPG"]=" 1"
D["JPEG_MEM_SRC_USES_CONST"]=" 1"
D["HAVE_LIBRAW"]=" 1"
D["HAVE_LIBCFITSIO"]=" 1"
D["HAVE_LIBBZ2"]=" 1"
D["HAVE_LIBZ"]=" 1"
D["HAVE_LIBLZMA"]=" 1"
D["HAVE_LIBUSB"]=" 1"
D["HAVE_LIBDC1394"]=" 1"
D["HAVE_LIBUVC"]=" 1"
D["HAVE_STATIC_LIBUVC"]=" 1"
D["HAVE_LIBDL"]=" 1"
D["HAVE_LIBGPHOTO2"]=" 1"
D["HAVE_ERRNO_H"]=" 1"
D["HAVE_FCNTL_H"]=" 1"
D["HAVE_FLOAT_H"]=" 1"
D["HAVE_LIMITS_H"]=" 1"
D["HAVE_MATH_H"]=" 1"
D["HAVE_STDINT_H"]=" 1"
D["HAVE_STDLIB_H"]=" 1"
D["HAVE_STRING_H"]=" 1"
D["HAVE_STRINGS_H"]=" 1"
D["HAVE_SYS_IOCTL_H"]=" 1"
D["HAVE_SYS_TIME_H"]=" 1"
D["HAVE_UNISTD_H"]=" 1"
D["HAVE_FITSIO_H"]=" 1"
D["HAVE_SYS_TIME_H"]=" 1"
D["HAVE_SYSLOG_H"]=" 1"
D["HAVE_STDBOOL_H"]=" 1"
D["HAVE_CERRNO"]=" 1"
D["HAVE_CFLOAT"]=" 1"
D["HAVE_CLIMITS"]=" 1"
D["HAVE_CMATH"]=" 1"
D["HAVE_CSTDINT"]=" 1"
D["HAVE_CSTDLIB"]=" 1"
D["HAVE_CSTRING"]=" 1"
D["HAVE_COREMEDIA_COREMEDIA_H"]=" 1"
D["HAVE_VIDEOTOOLBOX_VIDEOTOOLBOX_H"]=" 1"
D["HAVE__BOOL"]=" 1"
D["HAVE_STDLIB_H"]=" 1"
D["HAVE_MALLOC"]=" 1"
D["HAVE_STDLIB_H"]=" 1"
D["HAVE_REALLOC"]=" 1"
D["HAVE_GETCWD"]=" 1"
D["HAVE_GETTIMEOFDAY"]=" 1"
D["HAVE_SELECT"]=" 1"
D["HAVE_SQRT"]=" 1"
D["HAVE_BZERO"]=" 1"
D["HAVE_MEMSET"]=" 1"
D["HAVE_MEMCPY"]=" 1"
D["HAVE_STAT64"]=" 1"
D["HAVE_CLOCK_GETTIME"]=" 1"
D["HAVE_MKDIR"]=" 1"
D["HAVE_POW"]=" 1"
D["HAVE_STRCASECMP"]=" 1"
D["HAVE_STRCHR"]=" 1"
D["HAVE_STRCSPN"]=" 1"
D["HAVE_STRDUP"]=" 1"
D["HAVE_STRERROR"]=" 1"
D["HAVE_STRNCASECMP"]=" 1"
D["HAVE_STRNDUP"]=" 1"
D["HAVE_STRRCHR"]=" 1"
D["HAVE_STRSTR"]=" 1"
D["HAVE_STRTOUL"]=" 1"
D["HAVE_DECL_ASI_AUTO_MAX_EXP_MS"]=" 0"
D["USB_OVERFLOW_HANGS"]=" 1"
D["HAVE_LIBASI2"]=" 1"
D["HAVE_LIBZWOFW"]=" 1"
D["HAVE_STATIC_LIBEFWFILTER"]=" 1"
D["HAVE_LIBUVC"]=" 1"
D["HAVE_LIBTOUPCAM"]=" 1"
D["HAVE_LIBMALLINCAM"]=" 1"
D["HAVE_LIBALTAIRCAM"]=" 1"
D["HAVE_LIBALTAIRCAM_LEGACY"]=" 1"
D["HAVE_LIBSTARSHOOTG"]=" 1"
D["HAVE_LIBNNCAM"]=" 1"
D["HAVE_LIBQHYCCD"]=" 1"
D["HAVE_LIBOMEGONPROCAM"]=" 1"
D["HAVE_LIBSVBCAMERASDK"]=" 1"
D["HAVE_LIBMALLINCAM"]=" 1"
  for (key in D) D_is_set[key] = 1
  FS = ""
}
/^[\t ]*#[\t ]*(define|undef)[\t ]+[_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ][_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789]*([\t (]|$)/ {
  line = $ 0
  split(line, arg, " ")
  if (arg[1] == "#") {
    defundef = arg[2]
    mac1 = arg[3]
  } else {
    defundef = substr(arg[1], 2)
    mac1 = arg[2]
  }
  split(mac1, mac2, "(") #)
  macro = mac2[1]
  prefix = substr(line, 1, index(line, defundef) - 1)
  if (D_is_set[macro]) {
    # Preserve the white space surrounding the "#".
    print prefix "define", macro P[macro] D[macro]
    next
  } else {
    # Replace #undef with comments.  This is necessary, for example,
    # in the case of _POSIX_SOURCE, which is predefined and required
    # on some systems where configure will not decide to define it.
    if (defundef == "undef") {
      print "/*", prefix defundef, macro, "*/"
      next
    }
  }
}
{ print }
