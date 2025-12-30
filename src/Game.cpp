#include "../include/Game.hpp"

// Constructeur : Initialisation de la fenêtre
Game::Game()
    : window(sf::VideoMode({480, 640}), "Pacman"),
      grid()
{
    window.setFramerateLimit(60);
}

// Lance la boucle de jeu
void Game::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

// Gère les entrées (clavier, fermeture fenêtre)
void Game::processEvents() {
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
         window.close();
        }
    }
}

// Met à jour la logique du jeu
void Game::update() {
    // Logique du jeu à implémenter ici
}

// Affiche les éléments à l'écran
void Game::render() {
    window.clear(sf::Color::Black);
    grid.draw(window);
    window.display();
}