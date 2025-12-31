#pragma once
#include <SFML/Graphics.hpp>
#include "Map.hpp"

/**
 * @brief Classe représentant le jeu.
 * 
 * Cette classe représente le jeu Pac-Man.
 */
class Game {
public:
    /**
     * @brief Constructeur de la classe Game.
     */
    Game();
    /**
     * @brief Lance la boucle de jeu.
     */
    void run();

private:
    /**
     * @brief Gère les entrées (clavier, fermeture fenêtre).
     */
    void processEvents();
    /**
     * @brief Met à jour la logique du jeu.
     */
    void update();
    /**
     * @brief Affiche les éléments à l'écran.
     */
    void render();
    /**
     * @brief La fenêtre SFML.
     */
    sf::RenderWindow window;
    /**
     * @brief La carte du jeu.
     */
    Map grid;
};