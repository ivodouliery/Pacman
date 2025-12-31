#include "../include/Ghost.hpp"

Ghost::Ghost(GhostType type) : type(type), mode(GhostMode::SCATTER) {
    speed = 90.0f; // Slightly slower than Pacman
}

void Ghost::setPosition(float x, float y) {
    Entity::setPosition(x, y);
    sprite_eyes.setPosition({x + cellSize/2, y});
}