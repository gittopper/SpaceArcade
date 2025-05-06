cmake_minimum_required(VERSION 3.18)

option(ANDROID_REGIME "android regime" OFF)

project(SpaceArcade VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(GAME_SOURCES ${CMAKE_CURRENT_LIST_DIR}/src)

add_subdirectory(${GAME_SOURCES}/3rd_party)


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
        ${GAME_SOURCES}/game/font.cpp
        ${GAME_SOURCES}/game/font.h
        ${GAME_SOURCES}/game/collider.cpp
        ${GAME_SOURCES}/game/collider.h
        ${GAME_SOURCES}/game/camera.cpp
        ${GAME_SOURCES}/game/camera.h
        ${GAME_SOURCES}/game/level.cpp
        ${GAME_SOURCES}/game/level.h
        ${GAME_SOURCES}/game/overlay.cpp
        ${GAME_SOURCES}/game/overlay.h
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
        ${GAME_SOURCES}/game/pngreader.cpp
        ${GAME_SOURCES}/game/objects/asteroid.cpp
        ${GAME_SOURCES}/game/objects/asteroid.h
        ${GAME_SOURCES}/game/objects/bullet.cpp
        ${GAME_SOURCES}/game/objects/bullet.h
        ${GAME_SOURCES}/game/objects/scene.cpp
        ${GAME_SOURCES}/game/objects/scene.h
        ${GAME_SOURCES}/game/objects/spaceship.cpp
        ${GAME_SOURCES}/game/objects/spaceship.h
        ${GAME_SOURCES}/game/resourceloader.h
        ${GAME_SOURCES}/game/soundplayer.h
        ${GAME_SOURCES}/game/soundplayer.cpp
        ${GAME_SOURCES}/rendering/spacegamerenderer.cpp
        ${GAME_SOURCES}/rendering/spacegamerenderer.h
        ${GAME_SOURCES}/rendering/renderer.h
        ${GAME_SOURCES}/rendering/glesrenderer.cpp
        ${GAME_SOURCES}/rendering/glesrenderer.h
        ${GAME_SOURCES}/rendering/glesspacegamerenderer.cpp
        ${GAME_SOURCES}/rendering/glesspacegamerenderer.h
)

if(ANDROID_REGIME)

    list(APPEND ARCADE_SOURCES
            ${GAME_SOURCES}/android/GameEngine.cpp
            ${GAME_SOURCES}/android/androidresourceloader.cpp
    )
    set(TARGET GameEngine)
    message(ANDROID_ABI=${ANDROID_ABI})
    set(SFML_DIR ${CMAKE_CURRENT_LIST_DIR}/build/install/android/${CMAKE_BUILD_TYPE}/${ANDROID_ABI}/lib/${ANDROID_ABI}/cmake/SFML/)
    message(SFML_DIR=${SFML_DIR})
    find_package (SFML COMPONENTS Graphics Audio Window Network System)
    add_library(${TARGET} SHARED ${ARCADE_SOURCES})
    target_link_libraries(${TARGET} log android EGL GLESv2 OpenSLES
        dl  GLESv1_CM png_static zlibstatic SFML::Graphics SFML::Audio freetype)
    set_target_properties(${TARGET} PROPERTIES LIBRARY_OUTPUT_NAME ${TARGET})
    target_include_directories(${TARGET} PRIVATE ${GAME_SOURCES})

else()

    list(APPEND ARCADE_SOURCES
        ${GAME_SOURCES}/desktop/fileresourceloader.cpp
        ${GAME_SOURCES}/desktop/fileresourceloader.h
        )
    file(COPY ${GAME_SOURCES}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)
    set(CMAKE_AUTOUIC ON)

    find_package(Qt6 COMPONENTS Widgets OpenGL OpenGLWidgets Multimedia REQUIRED)

    add_executable(SpaceArcade
            QT/src/main.cpp
            QT/src/mainwindow.h
            QT/src/mainwindow.cpp
            ${ARCADE_SOURCES}
    )

    target_include_directories(SpaceArcade PUBLIC
            ${CMAKE_CURRENT_LIST_DIR}/QT/src
            ${GAME_SOURCES}
        )
    set(SFML_STATIC_LIBRARIES TRUE)
    find_package (SFML COMPONENTS Graphics Audio Window Network System
        REQUIRED PATHS ${CMAKE_CURRENT_LIST_DIR}/build/install/desktop/${CMAKE_BUILD_TYPE}/lib/cmake NO_DEFAULT_PATH )

    target_link_libraries(SpaceArcade Qt6::Widgets Qt6::OpenGL
        Qt6::OpenGLWidgets Qt6::Multimedia -lGL png_static zlibstatic SFML::Graphics SFML::Audio freetype)

endif()
