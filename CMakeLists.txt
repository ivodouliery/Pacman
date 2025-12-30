cmake_minimum_required(VERSION 3.16)
project(PacmanSolution LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Configuration SFML 3.0 ---
find_package(SFML 3 COMPONENTS Graphics Window System Audio REQUIRED)

# --- Détection automatique des sources ---
# On prend tous les .cpp dans src/ (Game.cpp, Map.cpp, Ghost.cpp, etc.)
file(GLOB SRC_FILES "src/*.cpp")

# On retire main.cpp de la liste car il ne doit pas être dans la librairie partagée
# (sinon on aurait deux fonctions main() lors des tests)
list(REMOVE_ITEM SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")

# --- Bibliothèque Core (Logique du jeu) ---
add_library(PacmanCore OBJECT ${SRC_FILES})

target_include_directories(PacmanCore PUBLIC include)
target_link_libraries(PacmanCore PUBLIC SFML::Graphics SFML::Window SFML::System SFML::Audio)

# --- Exécutable Principal (Jeu) ---
add_executable(Pacman src/main.cpp)
target_link_libraries(Pacman PRIVATE PacmanCore)

# Copie des assets
if(EXISTS "${CMAKE_SOURCE_DIR}/assets")
    add_custom_command(TARGET Pacman POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:Pacman>/assets
    )
endif()

# --- Exécutable de Tests (Catch2) ---
enable_testing()

set(TEST_SOURCES tests/test.cpp)
if(EXISTS "${CMAKE_SOURCE_DIR}/vendor/catch_amalgamated.cpp")
    list(APPEND TEST_SOURCES "vendor/catch_amalgamated.cpp")
endif()

add_executable(PacmanTests ${TEST_SOURCES})
target_include_directories(PacmanTests PRIVATE vendor)
target_link_libraries(PacmanTests PRIVATE PacmanCore)

add_test(NAME RunTests COMMAND PacmanTests)