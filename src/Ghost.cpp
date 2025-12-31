#include "../include/Ghost.hpp"

Ghost::Ghost(GhostType type) : type(type), mode(GhostMode::SCATTER) {
    speed = 90.0f; // Slightly slower than Pacman

    if(!texture.loadFromFile("./assets/ghosts.png")) {
        throw std::runtime_error("Failed to load texture");
    }
    sprite_body = sf::Sprite(texture);

    switch(type) {
        case GhostType::BLINKY: 
            sprite_body.setTextureRect(sf::IntRect({0*entitySize, 0*entitySize}, {entitySize, entitySize}));
            sprite_eyes.setTextureRect(sf::IntRect({0*eyesSize, eyesOriginY}, {eyesSize, eyesSize}));
            break;
        case GhostType::INKY: 
            sprite_body.setTextureRect(sf::IntRect({0*entitySize, 1*entitySize}, {entitySize, entitySize}));
            sprite_eyes.setTextureRect(sf::IntRect({1*eyesSize, eyesOriginY}, {eyesSize, eyesSize}));
            break;
        case GhostType::PINKY: 
            sprite_body.setTextureRect(sf::IntRect({0*entitySize, 2*entitySize}, {entitySize, entitySize}));
            sprite_eyes.setTextureRect(sf::IntRect({2*eyesSize, eyesOriginY}, {eyesSize, eyesSize}));
            break;
        case GhostType::CLYDE: 
            sprite_body.setTextureRect(sf::IntRect({0*entitySize, 3*entitySize}, {entitySize, entitySize}));
            sprite_eyes.setTextureRect(sf::IntRect({3*eyesSize, eyesOriginY}, {eyesSize, eyesSize}));
            break;
    }
}

void Ghost::setPosition(float x, float y) {
    Entity::setPosition(x, y);
    sprite_eyes.setPosition({x + 8.0f, y});
}

void Ghost::draw(sf::RenderWindow& window) {
    window.draw(sprite_body);
    window.draw(sprite_eyes);
}

void Ghost::update(float dt) {
    Entity::update(dt);
    animationTimer += dt;
    if(animationTimer >= animationSpeed) {
        animationTimer -= animationSpeed;
        currentFrame = (currentFrame + 1) % nbFrames;
        switch(type) {
            case GhostType::BLINKY: 
                sprite_body.setTextureRect(sf::IntRect({currentFrame * entitySize, 0*entitySize}, {entitySize, entitySize}));
                break;
            case GhostType::INKY: 
                sprite_body.setTextureRect(sf::IntRect({currentFrame * entitySize, 1*entitySize}, {entitySize, entitySize}));
                break;
            case GhostType::PINKY: 
                sprite_body.setTextureRect(sf::IntRect({currentFrame * entitySize, 2*entitySize}, {entitySize, entitySize}));
                break;
            case GhostType::CLYDE: 
                sprite_body.setTextureRect(sf::IntRect({currentFrame * entitySize, 3*entitySize}, {entitySize, entitySize}));
                break;
        }
    }
    
}

void Ghost::setRotation(int direction) {
    switch(direction) {
        case 0:
            sprite_eyes = sprite_eyes_up;
            break;
        case 1:
            sprite_eyes = sprite_eyes_down;
            break;
        default:
            sprite_eyes = sprite_eyes_left_right;
            break;
    }
}