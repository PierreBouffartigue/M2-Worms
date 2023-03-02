cmake_minimum_required(VERSION 3.24)
project(worms)

set(CMAKE_CXX_STANDARD 23)

add_executable(worms
        src/main.cpp
        GameEngine/IGame.h GameEngine/Scenes/IScene.h GameEngine/UI/IButton.cpp GameEngine/UI/IButton.h
        src/UI/Button.cpp src/UI/Button.h
        src/Game.cpp src/Game.h
        src/Scenes/EScenes.h src/Scenes/MainMenuScene.cpp src/Scenes/MainMenuScene.h src/Scenes/PlayGameScene.cpp src/Scenes/PlayGameScene.h
        src/Inputs/MouseEvents.cpp src/Inputs/MouseEvents.h src/Utils/Profiling.cpp src/Utils/Profiling.h src/Utils/Utils.cpp src/Utils/Utils.h src/Utils/Math.h
        src/GameObjects/Player.cpp src/GameObjects/Player.h src/GameObjects/Projectile.cpp src/GameObjects/Projectile.h
        src/Ground/Curve.cpp src/Ground/Curve.h src/Ground/Ground.cpp src/Ground/Ground.h)

# Remove line 11 - 12 if VCPKG is used
# SFML set on the racine of the project but you can change path
set(SFML_ROOT "../SFML-2.5.1")
set(SFML_STATIC_LIBRARIES TRUE)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    target_link_libraries(worms sfml-graphics sfml-window sfml-system)
endif ()

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()

# uncomment this line to show warnings
# set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
