cmake_minimum_required(VERSION 3.16)
project(Pacman LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set SFML path
set(SFML_DIR "C:/Users/alexi/OneDrive/Bureau/sfml/SFML-3.0.0/lib/cmake/SFML")

# Sources
set(SRC
    src/main.cpp
    src/Game.cpp
    src/Map.cpp
    src/Pacman.cpp
)

add_executable(Pacman ${SRC})

target_include_directories(Pacman PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Find SFML 3.0
find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

target_link_libraries(Pacman PRIVATE SFML::Graphics SFML::Window SFML::System)
