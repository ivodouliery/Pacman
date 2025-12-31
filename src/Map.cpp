#include "../include/Map.hpp"
#include <filesystem>
#include <iostream>

Map::Map(): blinky(GhostType::BLINKY), pinky(GhostType::PINKY), inky(GhostType::INKY), clyde(GhostType::CLYDE), pacman(), mapSprite(mapTexture), dotSprite(itemTexture), superDotSprite(itemTexture) {
    mapGrid = {
        "############################", 
        "#............##............#", 
        "#.####.#####.##.#####.####.#", 
        "#o####.#####.##.#####.####o#", 
        "#..........................#",
        "#.####.##.########.##.####.#", 
        "#.####.##.########.##.####.#",
        "#......##....##....##......#", 
        "######.##### ## #####.######", 
        "     #.##### ## #####.#     ",
        "     #.##    B     ##.#     ",
        "     #.## ###--### ##.#     ",
        "######.## ###--### ##.######",
        "      .   #I P C #   .      ",
        "######.## ######## ##.######",
        "     #.## ######## ##.#     ",
        "     #.##          ##.#     ",
        "     #.##### ## #####.#     ",
        "######.##### ## #####.######", 
        "#............##............#",
        "#.####.#####.##.#####.####.#",
        "#.####.#####.##.#####.####.#",
        "#o..##.......p .......##..o#",
        "###.##.##.########.##.##.###",
        "###.##.##.########.##.##.###",
        "#......##....##....##......#",
        "#.##########.##.##########.#",
        "#.##########.##.##########.#",
        "#..........................#",
        "############################"
    };

    if (!itemTexture.loadFromFile("./assets/items.png")) {
        std::cerr << "Erreur: Impossible de charger assets/items.png" << std::endl;
    }

    if (!mapStartTexture.loadFromFile("./assets/map_start.png")) {
        std::cerr << "Erreur: Impossible de charger assets/map_start.png" << std::endl;
    }

    if (!mapTexture.loadFromFile("./assets/map.png")) {
        std::cerr << "Erreur: Impossible de charger assets/map.png" << std::endl;
    }

    mapSprite = sf::Sprite(mapStartTexture);

    dotSprite.setTextureRect(sf::IntRect({0 * itemSize, 1 * itemSize}, {itemSize, itemSize}));

    superDotSprite.setTextureRect(sf::IntRect({1 * itemSize, 1 * itemSize}, {itemSize, itemSize}));

    // Initialisation des positions
    for (int y = 0; y < MAP_HEIGHT; ++y) {
        for (int x = 0; x < MAP_WIDTH; ++x) {
            float posX = gridOriginX + x * Entity::cellSize;
            float posY = gridOriginY + y * Entity::cellSize;
            char cell = mapGrid[y][x];
            
            switch(cell) {
                case 'p':
                    pacman.setPosition(posX, posY);
                    break;
                case 'B':
                    blinky.setPosition(posX, posY);
                    break;
                case 'P':
                    pinky.setPosition(posX, posY);
                    break;
                case 'I':
                    inky.setPosition(posX, posY);
                    break;
                case 'C':
                    clyde.setPosition(posX, posY);
                    break;
            }
        }
    }

}

void Map::draw(sf::RenderWindow& window) {
    sf::Texture mapTexture("./assets/map.png");
    sf::Sprite map(mapTexture);
    window.draw(map);

    sf::Texture itemTexture("./assets/items.png");
    sf::Sprite dot(itemTexture);
    dot.setTextureRect(sf::IntRect({ 0 * itemSize, 1 * itemSize }, { itemSize, itemSize }));
    sf::Sprite superDot(itemTexture);
    superDot.setTextureRect(sf::IntRect({ 1 * itemSize, 1 * itemSize }, { itemSize, itemSize }));

    for (int y = 0; y < MAP_HEIGHT; ++y) {
        for (int x = 0; x < MAP_WIDTH; ++x) {
            switch (mapGrid[y][x]) {
            case '.':
                dot.setPosition({ gridOriginX + static_cast<float>(x) * static_cast<float>(itemSize), gridOriginY + static_cast<float>(y) * static_cast<float>(itemSize) });
                window.draw(dot);
                break;
            case 'o':
                superDot.setPosition({ gridOriginX + static_cast<float>(x) * static_cast<float>(itemSize), gridOriginY + static_cast<float>(y) * static_cast<float>(itemSize) });
                window.draw(superDot);
                break;
            }
        }
    }

}
