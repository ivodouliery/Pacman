#include "../include/Entity.hpp"

Entity::Entity()
    : position(0.f, 0.f), direction(0.f, 0.f), speed(0.f), animationTimer(0.0f), currentFrame(0), nbFrames(4), sprite_body(texture) {
}

void Entity::setPosition(float x, float y) {
    position = {x, y - cellSize / 2.0f};
    sprite_body.setPosition(position);
}

sf::Vector2f Entity::getPosition() const {
    return position;
}

void Entity::update(float dt) {
    position += direction * speed * dt;
}

void Entity::setSpeed(float speed) {
    this->speed = speed;
}

float Entity::getSpeed() const {
    return speed;
}

void Entity::setDirection(sf::Vector2f direction) {
    this->direction = direction;
}

sf::Vector2f Entity::getDirection() const {
    return direction;
}
