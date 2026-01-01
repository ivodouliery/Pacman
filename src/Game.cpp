#include "../include/Game.hpp"

// Constructeur : Initialisation de la fenêtre
Game::Game() 
    : window(sf::VideoMode({480, 640}), "Pacman") 
{
    window.setFramerateLimit(60);
}

// Lance la boucle de jeu
void Game::run() {
    while (window.isOpen()) {
        processEvents();
        if (state == GameState::PLAYING) {
            update();
        }
        render();
    }
}

// Gère les entrées (clavier, fermeture fenêtre)
void Game::processEvents() {
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
        else if (const auto* keyEvent = event->getIf<sf::Event::KeyPressed>()) {
            if (state == GameState::START) {
                state = GameState::PLAYING;
                grid.start();
                grid.handleInput(keyEvent->code);
            } else if (state == GameState::PLAYING) {
                grid.handleInput(keyEvent->code);
            }
        }
    }
}

// Met à jour la logique du jeu
void Game::update() {
    grid.update();
}

// Affiche les éléments à l'écran
void Game::render() {
    window.clear();
    grid.draw(window);
    window.display();
}
