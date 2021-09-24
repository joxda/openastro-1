# Generating the library showControls
set(project "showControls")

set(${project}, "")
list(APPEND ${project}_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/showControls.c
)
add_executable(showControls ${${project}_SOURCES} )
# Generating the library showFeatures
set(project "showFeatures")

set(${project}, "")
list(APPEND ${project}_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/showFeatures.c
)
add_executable(showFeatures ${${project}_SOURCES} )
# Generating the library logging
set(project "logging")

set(${project}, "")
list(APPEND ${project}_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/logging.c
)
add_executable(logging ${${project}_SOURCES} )
# Generating the library startStreaming
set(project "startStreaming")

set(${project}, "")
list(APPEND ${project}_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/startStreaming.c
)
add_executable(startStreaming ${${project}_SOURCES} )
# Generating the library \
set(project "_")

set(${project}, "")
list(APPEND ${project}_SOURCES
    
)
add_executable(\ ${${project}_SOURCES} )
