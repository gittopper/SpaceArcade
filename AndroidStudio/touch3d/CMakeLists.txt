cmake_minimum_required(VERSION 3.18)
set(SOURCES_ROOT ./)
set(SOURCES
        ${SOURCES_ROOT}/jni/camera.cpp
        ${SOURCES_ROOT}/jni/Matrix.cpp
        ${SOURCES_ROOT}/jni/Native.cpp
        ${SOURCES_ROOT}/jni/renderer.cpp
        ${SOURCES_ROOT}/jni/puzzle/box.cpp
        ${SOURCES_ROOT}/jni/puzzle/mat.cpp
        ${SOURCES_ROOT}/jni/puzzle/piece.cpp
        ${SOURCES_ROOT}/jni/puzzle/solver.cpp
        ${SOURCES_ROOT}/jni/puzzle/utils.cpp
        ${SOURCES_ROOT}/jni/puzzle/utils3d.cpp
        ${SOURCES_ROOT}/jni/puzzle/vector.cpp
        ${SOURCES_ROOT}/jni/puzzle/volpart.cpp
        ${SOURCES_ROOT}/jni/puzzle/volumepuzzle.cpp
        ${SOURCES_ROOT}/jni/puzzle/print.cpp
        ${SOURCES_ROOT}/jni/puzzle/pieceshower.cpp
        )
set(TARGET Native)
add_library(${TARGET} SHARED ${SOURCES})
target_include_directories(${TARGET} PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/jni
        ${CMAKE_CURRENT_LIST_DIR}/jni/puzzle
        )
target_link_libraries(${TARGET} PUBLIC log android EGL GLESv2 OpenSLES  dl  GLESv1_CM)
set_target_properties(${TARGET} PROPERTIES LIBRARY_OUTPUT_NAME ${TARGET})
target_include_directories(${TARGET} PRIVATE ${SOURCES_ROOT})

