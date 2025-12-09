#pragma once
#include <SFML/Graphics.hpp>
#include "Map.hpp"

class Game {
public:
    Game(); // Constructeur
    void run(); // Lance la boucle de jeu

private:
    void processEvents(); // Gère les entrées (clavier, fermeture fenêtre)
    void update();        // Met à jour la logique du jeu
    void render();        // Affiche les éléments à l'écran

    sf::RenderWindow window; // La fenêtre SFML
    Map grid;
};