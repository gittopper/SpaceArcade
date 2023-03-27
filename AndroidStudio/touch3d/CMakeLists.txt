cmake_minimum_required(VERSION 3.18)
set(SOURCES
        jni/camera.cpp
        jni/Matrix.cpp
        jni/Native.cpp
        jni/renderer.cpp
        )
set(TARGET Native)
add_library(${TARGET} SHARED ${SOURCES})
target_include_directories(${TARGET} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/jni)
target_link_libraries(${TARGET} PUBLIC log android EGL GLESv2 OpenSLES  dl  GLESv1_CM)
set_target_properties(${TARGET} PROPERTIES LIBRARY_OUTPUT_NAME ${TARGET})
target_include_directories(${TARGET} PRIVATE ${SOURCES_ROOT})

