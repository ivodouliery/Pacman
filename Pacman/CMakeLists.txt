cmake_minimum_required(VERSION 3.22)

# Nom du projet
project(Pacman VERSION 1.0.0 LANGUAGES CXX)

# On veut utiliser le C++ 17 (standard moderne)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Trouver SFML (vcpkg s'en occupe tout seul si installé)
find_package(SFML COMPONENTS Graphics Audio Window System REQUIRED)

# Ajouter tes fichiers .cpp ici (ajoute les nouveaux fichiers à cette liste quand tu en crées)
add_executable(Pacman
    main.cpp
    # Ajouter d'autres fichiers ici, ex: Fantome.cpp
)

# Lier SFML à ton exécutable
target_link_libraries(Pacman PRIVATE SFML::Graphics SFML::Audio SFML::Window SFML::System)