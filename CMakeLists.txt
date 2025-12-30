cmake_minimum_required(VERSION 3.12)

project(Pacman VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 3.0 COMPONENTS Graphics Window System Audio REQUIRED)

set(SOURCES
    src/main.cpp
    src/Game.cpp
    src/Ghost.cpp
    src/Map.cpp
)

set(HEADERS
    include/Game.hpp
    include/Ghost.hpp
    include/Map.hpp
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PRIVATE include)

target_link_libraries(${PROJECT_NAME} PRIVATE 
    SFML::Graphics 
    SFML::Window 
    SFML::System 
    SFML::Audio
)

find_package(Catch2 3 REQUIRED)
enable_testing()

add_executable(PacmanTests 
    tests/test.cpp
    src/Game.cpp
    src/Ghost.cpp
    src/Map.cpp
)

target_link_libraries(PacmanTests PRIVATE 
    Catch2::Catch2WithMain
    SFML::Graphics 
    SFML::Window 
    SFML::System 
    SFML::Audio
)

target_include_directories(PacmanTests PRIVATE include)

include(Catch)
catch_discover_tests(PacmanTests)
