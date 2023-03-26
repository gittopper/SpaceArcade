cmake_minimum_required(VERSION 3.18)
file(GLOB SOURCES jni/*.cpp)
set(TARGET Native)
add_library(${TARGET} SHARED ${SOURCES})
target_link_libraries(${TARGET} log android EGL GLESv2 OpenSLES  dl  GLESv1_CM)
set_target_properties(${TARGET} PROPERTIES LIBRARY_OUTPUT_NAME ${TARGET})
target_include_directories(${TARGET} PRIVATE ${SOURCES_ROOT})

