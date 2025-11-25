#include "../include/Game.hpp"

// Constructeur : Initialisation de la fenêtre
Game::Game() 
    : mWindow(sf::VideoMode({800, 600}), "Pac-Man C++ / SFML 3") 
{
    mWindow.setFramerateLimit(60);
}

// Lance la boucle de jeu
void Game::run() {
    while (mWindow.isOpen()) {
        processEvents();
        update();
        render();
    }
}