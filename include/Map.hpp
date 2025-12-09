#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Map {
public:
    Map();
    void draw(sf::RenderWindow& window);

private:
    std::vector<std::string> mGrid;
    float mcellSize = 40.0f; // Taille d'une case (ex: 40x40 pixels)
};
