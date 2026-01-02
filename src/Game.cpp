#include "../include/Game.hpp"

/**
 * @brief Constructeur : Initialisation de la fenêtre.
 * 
 * Crée une fenêtre de 480x640 pixels avec le titre "Pacman".
 * Limite le framerate à 60 FPS pour une fluidité constante.
 */
Game::Game() 
    : window(sf::VideoMode({480, 640}), "Pacman") 
{
    window.setFramerateLimit(60);
}

/**
 * @brief Lance la boucle de jeu.
 * 
 * Maintient la fenêtre ouverte et appelle séquentiellement :
 * - processEvents() : Gestion des entrées.
 * - update() : Mise à jour de la logique (si le jeu est en cours).
 * - render() : Affichage.
 */
void Game::run() {
    while (window.isOpen()) {
        processEvents();
        if (state == GameState::PLAYING) {
            update();
        }
        render();
    }
}

/**
 * @brief Gère les entrées (clavier, fermeture fenêtre).
 * 
 * Traite la file d'événements SFML.
 * - Fermeture de la fenêtre.
 * - Appui sur une touche :
 *   - Si le jeu n'a pas commencé, le lance.
 *   - Transmet la touche à la carte (Map) pour contrôler Pacman.
 */
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

/**
 * @brief Met à jour la logique du jeu.
 * 
 * Délègue la mise à jour à l'objet Map.
 */
void Game::update() {
    grid.update();
}

/**
 * @brief Affiche les éléments à l'écran.
 * 
 * Efface l'écran, demande à la Map de se dessiner, puis affiche le buffer.
 */
void Game::render() {
    window.clear();
    grid.draw(window);
    window.display();
}
