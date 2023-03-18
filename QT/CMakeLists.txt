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

add_executable(SpaceArcade
    src/main.cpp
    src/mainwindow.h
    src/mainwindow.cpp
    ${GAME_SOURCES}/math/vector.cpp
    ${GAME_SOURCES}/math/boundingbox.cpp
    ${GAME_SOURCES}/math/mat.cpp
    ${GAME_SOURCES}/math/mat44.cpp
    ${GAME_SOURCES}/math/mathutils.cpp
    ${GAME_SOURCES}/math/vector4.cpp
    ${GAME_SOURCES}/game/collider.cpp
    ${GAME_SOURCES}/game/collisionrules.cpp
    ${GAME_SOURCES}/game/igame.cpp
    ${GAME_SOURCES}/game/iobject.cpp
    ${GAME_SOURCES}/game/physics.cpp
    ${GAME_SOURCES}/game/regressvisitor.cpp
    ${GAME_SOURCES}/game/spacegame.cpp
    ${GAME_SOURCES}/game/objects/asteroid.cpp
    ${GAME_SOURCES}/game/objects/bullet.cpp
    ${GAME_SOURCES}/game/objects/scene.cpp
    ${GAME_SOURCES}/game/objects/spaceship.cpp
    ${GAME_SOURCES}/rendering/openglrenderer.cpp
    ${GAME_SOURCES}/rendering/spacegamerenderer.cpp
    )

target_include_directories(SpaceArcade PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/src
    ${GAME_SOURCES}
    )
target_link_libraries(SpaceArcade Qt5::Widgets Qt5::OpenGL  -lGL)
