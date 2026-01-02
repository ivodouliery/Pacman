#pragma once
#include <SFML/Graphics.hpp>
#include "Map.hpp"

/**
 * @file Game.hpp
 * @brief Définition de la classe principale du jeu.
 * 
 * Ce fichier contient la déclaration de la classe Game qui gère la boucle principale,
 * les événements, la mise à jour et le rendu du jeu Pacman.
 */

/**
 * @class Game
 * @brief Classe principale gérant le cycle de vie du jeu.
 * 
 * La classe Game encapsule la fenêtre SFML, la boucle de jeu principale
 * et délègue la logique spécifique à la carte (Map) et aux entités.
 */
class Game {
public:
    /**
     * @brief Constructeur de la classe Game.
     * 
     * Initialise la fenêtre de jeu avec les paramètres par défaut (taille, titre, framerate).
     */
    Game();

    /**
     * @brief Lance la boucle principale du jeu.
     * 
     * Cette méthode contient la boucle while(window.isOpen()) qui appelle
     * successivement processEvents(), update() et render() à chaque frame.
     */
    void run();

private:
    /**
     * @brief Gère les événements utilisateur.
     * 
     * Traite les entrées clavier pour contrôler le jeu et les événements système
     * comme la fermeture de la fenêtre.
     */
    void processEvents();

    /**
     * @brief Met à jour la logique du jeu.
     * 
     * Appelle la méthode update de la carte (grid) si le jeu est en cours.
     */
    void update();

    /**
     * @brief Affiche les éléments du jeu à l'écran.
     * 
     * Efface la fenêtre, dessine la carte et ses entités, puis affiche le rendu.
     */
    void render();

    /**
     * @brief La fenêtre de rendu SFML.
     */
    sf::RenderWindow window;

    /**
     * @enum GameState
     * @brief Énumération représentant les différents états possibles du jeu.
     */
    enum class GameState {
        START,   /**< Écran de démarrage ou état d'attente avant le début du jeu. */
        PLAYING  /**< Le jeu est en cours d'exécution. */
    };

    /**
     * @brief État actuel du jeu.
     * 
     * Initialisé à GameState::START.
     */
    GameState state = GameState::START;

    /**
     * @brief Instance de la carte du jeu.
     * 
     * Gère la grille, Pacman, les fantômes et la logique de jeu associée.
     */
    Map grid;
};