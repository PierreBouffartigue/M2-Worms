cmake_minimum_required(VERSION 3.24)
project(worms)

set(CMAKE_CXX_STANDARD 23)

add_executable(worms
        src/main.cpp "src/Projection.h")

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

set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
