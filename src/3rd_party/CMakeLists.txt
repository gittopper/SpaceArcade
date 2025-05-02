include(ExternalProject)

set(ZLIB_BUILD_EXAMPLES CACHE BOOL OFF FORCE)
add_subdirectory(zlib)

set(PNG_TESTS CACHE BOOL OFF FORCE)
set(PNG_TOOLS CACHE BOOL OFF FORCE)
add_subdirectory(libpng)

#set(SFML_OS_LINUX CACHE BOOL ON FORCE)
#set(SFML_BUILD_FRAMEWORKS CACHE BOOL ON FORCE)
#add_subdirectory(SFML)
