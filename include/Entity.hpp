#pragma once
#include <SFML/Graphics.hpp>

class Entity {
public:
    Entity();

    virtual ~Entity() = default;

    virtual void setPosition(float x, float y);
    sf::Vector2f getPosition() const;

    void setSpeed(float speed);
    float getSpeed() const;

    void setDirection(sf::Vector2f direction);
    sf::Vector2f getDirection() const;

protected:
    sf::Vector2f position;
    sf::Vector2f direction;
    float speed;

};
