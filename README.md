# Pacman

Un clone classique de Pacman écrit en C++ moderne (C++17) utilisant la bibliothèque SFML.

## Prérequis

Avant de commencer, assurez-vous d'avoir installé les outils suivants sur votre machine :

*   **Compilateur C++** compatible C++17 (GCC, Clang, MSVC).
*   **CMake** (version 3.12 ou supérieure).
*   **SFML** (version 3.0).
    *   *Note : Assurez-vous que SFML est correctement installé et accessible par CMake (via `find_package`).*
*   **Catch2** (version 3, pour les tests unitaires).

## Installation

1.  **Cloner le dépôt :**

    ```bash
    git clone https://github.com/ivodouliery/Pacman.git
    cd Pacman
    ```

2.  **Créer le dossier de build :**

    ```bash
    mkdir build
    cd build
    ```

3.  **Configurer le projet avec CMake :**

    ```bash
    cmake ..
    ```

4.  **Compiler le projet :**

    ```bash
    cmake --build .
    ```

## Lancement du Jeu

Une fois la compilation terminée, vous pouvez lancer le jeu depuis le dossier `build` :

*   **Sur macOS / Linux :**
    ```bash
    ./Pacman
    ```
*   **Sur Windows :**
    ```cmd
    Pacman.exe
    ```

## Contrôles

*   **Flèches directionnelles** : Déplacer Pacman (Haut, Bas, Gauche, Droite).
*   **Fermer la fenêtre** : Quitter le jeu.

## Tests Unitaires

Le projet inclut une suite de tests unitaires utilisant le framework Catch2. Pour les exécuter :

1.  Assurez-vous d'avoir compilé le projet (les tests sont compilés en même temps que le jeu).
2.  Lancez l'exécutable de test :

    *   **Sur macOS / Linux :**
        ```bash
        ./PacmanTests
        ```
    *   **Sur Windows :**
        ```cmd
        PacmanTests.exe
        ```

## Structure du Projet

*   `src/` : Code source (.cpp).
*   `include/` : En-têtes (.hpp).
*   `assets/` : Ressources graphiques (images, polices).
*   `tests/` : Tests unitaires.
*   `CMakeLists.txt` : Configuration de build CMake.
