#pragma once
#include "Entity.hpp"

class Pacman : public Entity {
public:
    Pacman();

    void draw(sf::RenderWindow& window) override;
    void update(float dt) override;
};
