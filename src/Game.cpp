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

// Gère les entrées (clavier, fermeture fenêtre)
void Game::processEvents() {
    while (const std::optional event = mWindow.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            mWindow.close();
        }
    }
}

// Met à jour la logique du jeu
void Game::update() {
    // Logique du jeu à implémenter ici
}

// Affiche les éléments à l'écran
void Game::render() {
    mWindow.clear(sf::Color::Black);
    mMap.draw(mWindow);
    mWindow.display();
}