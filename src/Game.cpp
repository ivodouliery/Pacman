#include "../include/Game.hpp"


Game::Game() 
    : window(sf::VideoMode({480, 640}), "Pacman") 
{
    window.setFramerateLimit(60);
}


void Game::run() {
    while (window.isOpen()) {
        processEvents();
        if (state == GameState::PLAYING) {
            update();
        }
        render();
    }
}


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


void Game::update() {
    grid.update();
}


void Game::render() {
    window.clear();
    grid.draw(window);
    window.display();
}
