cmake_minimum_required(VERSION 3.1.0)
project(SpaceArcade VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Widgets OpenGL REQUIRED)

set(GAME_SOURCES ${CMAKE_CURRENT_LIST_DIR}/../src)

set(ANDROID_REGIME OFF CACHE BOOL "" FORCE)

set(ARCADE_SOURCES
    ${GAME_SOURCES}/math/vector.cpp
    ${GAME_SOURCES}/math/vector.h
    ${GAME_SOURCES}/math/boundingbox.cpp
    ${GAME_SOURCES}/math/boundingbox.h
    ${GAME_SOURCES}/math/mat.cpp
    ${GAME_SOURCES}/math/mat.h
    ${GAME_SOURCES}/math/mat44.cpp
    ${GAME_SOURCES}/math/mat44.h
    ${GAME_SOURCES}/math/mathutils.cpp
    ${GAME_SOURCES}/math/mathutils.h
    ${GAME_SOURCES}/math/vector4.cpp
    ${GAME_SOURCES}/math/vector4.h
    ${GAME_SOURCES}/game/collider.cpp
    ${GAME_SOURCES}/game/collider.h
    ${GAME_SOURCES}/game/collisionrules.cpp
    ${GAME_SOURCES}/game/collisionrules.h
    ${GAME_SOURCES}/game/gameconfig.h
    ${GAME_SOURCES}/game/igame.cpp
    ${GAME_SOURCES}/game/igame.h
    ${GAME_SOURCES}/game/iobject.cpp
    ${GAME_SOURCES}/game/iobject.h
    ${GAME_SOURCES}/game/visitor.h
    ${GAME_SOURCES}/game/physics.cpp
    ${GAME_SOURCES}/game/physics.h
    ${GAME_SOURCES}/game/regressvisitor.cpp
    ${GAME_SOURCES}/game/regressvisitor.h
    ${GAME_SOURCES}/game/spacegame.cpp
    ${GAME_SOURCES}/game/spacegame.h
    ${GAME_SOURCES}/game/objects/asteroid.cpp
    ${GAME_SOURCES}/game/objects/asteroid.h
    ${GAME_SOURCES}/game/objects/bullet.cpp
    ${GAME_SOURCES}/game/objects/bullet.h
    ${GAME_SOURCES}/game/objects/scene.cpp
    ${GAME_SOURCES}/game/objects/scene.h
    ${GAME_SOURCES}/game/objects/spaceship.cpp
    ${GAME_SOURCES}/game/objects/spaceship.h
    ${GAME_SOURCES}/rendering/openglrenderer.cpp
    ${GAME_SOURCES}/rendering/openglrenderer.h
    ${GAME_SOURCES}/rendering/spacegamerenderer.cpp
    ${GAME_SOURCES}/rendering/spacegamerenderer.h
    ${GAME_SOURCES}/rendering/renderer.h
    ${GAME_SOURCES}/rendering/resourceloader.h
    )

if(ANDROID_REGIME)
    list(APPEND ARCADE_SOURCES
        ${GAME_SOURCES}/rendering/rendererfactory.cpp
        ${GAME_SOURCES}/rendering/rendererfactory.h
        ${GAME_SOURCES}/rendering/glesrenderer.cpp
        ${GAME_SOURCES}/rendering/glesrenderer.h
        ${GAME_SOURCES}/rendering/glesspacegamerenderer.cpp
        ${GAME_SOURCES}/rendering/glesspacegamerenderer.h
        ${GAME_SOURCES}/rendering/fileresourceloader.cpp
        ${GAME_SOURCES}/rendering/fileresourceloader.h
        ${GAME_SOURCES}/rendering/androidresourceloader.cpp
        ${GAME_SOURCES}/rendering/androidresourceloader.h
        ${GAME_SOURCES}/android/GameEngine.cpp
        )
endif()

add_executable(SpaceArcade
    src/main.cpp
    src/mainwindow.h
    src/mainwindow.cpp
    ${ARCADE_SOURCES}
    )


if(ANDROID_REGIME)
    target_include_directories(SpaceArcade PUBLIC
        ${GAME_SOURCES}
        )
endif()

target_include_directories(SpaceArcade PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/src
    ${GAME_SOURCES}
    )
target_link_libraries(SpaceArcade Qt5::Widgets Qt5::OpenGL  -lGL)
