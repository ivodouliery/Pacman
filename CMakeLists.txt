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


if(WIN32)
    # Sur Windows, WIN32 évite d'ouvrir une console noire en arrière-plan
    # Si vous voulez voir les std::cout, retirez "WIN32"
    add_executable(${PROJECT_NAME} WIN32
        ${SOURCES} 
        ${HEADERS} 
        include/Entity.hpp src/Entity.cpp
        include/Pacman.hpp src/Pacman.cpp
    )
else()
    add_executable(${PROJECT_NAME} 
        ${SOURCES} 
        ${HEADERS} 
        include/Entity.hpp src/Entity.cpp
        include/Pacman.hpp src/Pacman.cpp
    )
endif()

# Copie automatique du dossier assets à côté de l'exécutable après la compilation
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
    COMMENT "Copie des assets dans le dossier de build..."
)

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
    src/Entity.cpp
    src/Pacman.cpp
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
