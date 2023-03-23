cmake_minimum_required(VERSION 3.18)
set(SOURCES_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../../src/)
set(TARGET GameEngine)
set(SOURCES
        ${SOURCES_ROOT}/android/GameEngine.cpp
        ${SOURCES_ROOT}/math/vector.cpp
        ${SOURCES_ROOT}/math/boundingbox.cpp
        ${SOURCES_ROOT}/math/mat.cpp
        ${SOURCES_ROOT}/math/mat44.cpp
        ${SOURCES_ROOT}/math/mathutils.cpp
        ${SOURCES_ROOT}/math/vector4.cpp
        ${SOURCES_ROOT}/game/collider.cpp
        ${SOURCES_ROOT}/game/collisionrules.cpp
        ${SOURCES_ROOT}/game/igame.cpp
        ${SOURCES_ROOT}/game/iobject.cpp
        ${SOURCES_ROOT}/game/physics.cpp
        ${SOURCES_ROOT}/game/regressvisitor.cpp
        ${SOURCES_ROOT}/game/spacegame.cpp
        ${SOURCES_ROOT}/game/objects/asteroid.cpp
        ${SOURCES_ROOT}/game/objects/bullet.cpp
        ${SOURCES_ROOT}/game/objects/scene.cpp
        ${SOURCES_ROOT}/game/objects/spaceship.cpp
        ${SOURCES_ROOT}/rendering/glesrenderer.cpp
        ${SOURCES_ROOT}/rendering/glesspacegamerenderer.cpp
        ${SOURCES_ROOT}/rendering/rendererfactory.cpp
        ${SOURCES_ROOT}/rendering/androidresourceloader.cpp
        ${SOURCES_ROOT}/rendering/spacegamerenderer.cpp
        )

add_library(${TARGET} SHARED ${SOURCES})
target_link_libraries(${TARGET} log android EGL GLESv2 OpenSLES  dl  GLESv1_CM)
set_target_properties(${TARGET} PROPERTIES LIBRARY_OUTPUT_NAME ${TARGET})
target_include_directories(${TARGET} PRIVATE ${SOURCES_ROOT})
