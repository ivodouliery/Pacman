#include "../include/Pacman.hpp"

Pacman::Pacman() {
    speed = 100.0f; // Default speed
    if(!texture.loadFromFile("./assets/pacman.png")) {
        throw std::runtime_error("Failed to load texture");
    }
    sprite_body = sf::Sprite(texture);
    sprite_body.setTextureRect(sf::IntRect({1*entitySize, 0}, {entitySize, entitySize}));
}

void Pacman::draw(sf::RenderWindow& window) {
    window.draw(sprite_body);
}

void Pacman::update(float dt) {
    Entity::update(dt);
    // Input handling will go here (or be passed in)
}
