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

void Pacman::update(float dt, const std::vector<std::string>& map) {
    Entity::update(dt, map);
    animationTimer += dt;
    if (animationTimer >= animationSpeed) {
        animationTimer -= animationSpeed;
        currentFrame = (currentFrame + 1) % nbFrames;
        sprite_body.setTextureRect(sf::IntRect({currentFrame * entitySize, 0}, {entitySize, entitySize}));
    }
    sprite_body.setPosition(position);
    sprite_body.setOrigin({entitySize / 2, entitySize / 2});
    if(direction == sf::Vector2f{1.f, 0.f}) {
        sprite_body.setRotation(sf::degrees(0.0f));
    } else if(direction == sf::Vector2f{-1.f, 0.f}) {
        sprite_body.setRotation(sf::degrees(180.0f));
    } else if(direction == sf::Vector2f{0.f, 1.f}) {
        sprite_body.setRotation(sf::degrees(90.0f));
    } else if(direction == sf::Vector2f{0.f, -1.f}) {
        sprite_body.setRotation(sf::degrees(-90.0f));
    }
}

void Pacman::setPosition(float x, float y) {
    position = {x + cellSize, y + cellSize / 2.0f};
    sprite_body.setPosition(position);
}

