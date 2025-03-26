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

find_package(Qt6 COMPONENTS Widgets OpenGL OpenGLWidgets Multimedia REQUIRED)

set(GAME_SOURCES ${CMAKE_CURRENT_LIST_DIR}/src)

add_subdirectory(${GAME_SOURCES}/3rd_party)

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
    ${GAME_SOURCES}/game/resourceloader.h
    ${GAME_SOURCES}/rendering/spacegamerenderer.cpp
    ${GAME_SOURCES}/rendering/spacegamerenderer.h
    ${GAME_SOURCES}/rendering/renderer.h
    )

if(ANDROID_REGIME)
    list(APPEND ARCADE_SOURCES
        ${GAME_SOURCES}/android/rendererfactory.cpp
        ${GAME_SOURCES}/android/rendererfactory.h
        ${GAME_SOURCES}/android/glesrenderer.cpp
        ${GAME_SOURCES}/android/glesrenderer.h
        ${GAME_SOURCES}/android/glesspacegamerenderer.cpp
        ${GAME_SOURCES}/android/glesspacegamerenderer.h
        ${GAME_SOURCES}/android/androidresourceloader.cpp
        ${GAME_SOURCES}/android/androidresourceloader.h
        ${GAME_SOURCES}/android/GameEngine.cpp
        )
else()
    list(APPEND ARCADE_SOURCES
        ${GAME_SOURCES}/desktop/fileresourceloader.cpp
        ${GAME_SOURCES}/desktop/fileresourceloader.h
        ${GAME_SOURCES}/desktop/openglrenderer.cpp
        ${GAME_SOURCES}/desktop/openglrenderer.h
        ${GAME_SOURCES}/desktop/soundplayer.cpp
        ${GAME_SOURCES}/desktop/soundplayer.h
        )
    file(COPY ${GAME_SOURCES}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif()

add_executable(SpaceArcade
    QT/src/main.cpp
    QT/src/mainwindow.h
    QT/src/mainwindow.cpp
    ${ARCADE_SOURCES}
    )


if(ANDROID_REGIME)
    target_include_directories(SpaceArcade PUBLIC
        ${GAME_SOURCES}
        )
endif()

target_include_directories(SpaceArcade PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/QT/src
    ${GAME_SOURCES}
    ${GAME_SOURCES}/3rd_party/libpng
    )
target_link_libraries(SpaceArcade Qt6::Widgets Qt6::OpenGL Qt6::OpenGLWidgets Qt6::Multimedia  -lGL -lpng)

