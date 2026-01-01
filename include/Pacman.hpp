#pragma once
#include "Entity.hpp"

class Pacman : public Entity {
public:
    Pacman();
    void draw(sf::RenderWindow& window) override;
    void update(float dt, const std::vector<std::string>& map) override;
    void setPosition(float x, float y) override;
    
    void removeLife() { lives--; }
    int getLives() const { return lives; }
    void resetLives() { lives = 3; }
    
private:
    int lives = 3;
};
