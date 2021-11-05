cmake_minimum_required(VERSION 3.11)

add_library(oautil STATIC llist.c exp10.c logging.c)
add_library(liboacam::oautil ALIAS oautil)

set_target_properties(oautil PROPERTIES OUTPUT_NAME "oautil")
set_target_properties(oautil PROPERTIES POSITION_INDEPENDENT_CODE TRUE)

target_include_directories( oautil PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include )
target_include_directories( oautil PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/../ )

install(TARGETS oautil EXPORT oautil LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(EXPORT oautil DESTINATION ${CMAKE_INSTALL_BINDIR}/cmake/liboacam NAMESPACE liboacam:: DESTINATION "liboautilConfigTargets.cmake")