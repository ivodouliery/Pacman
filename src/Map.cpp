#include "../include/Map.hpp"
#include <filesystem>
#include <iostream>

Map::Map() {

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

};

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

bool Map::isWall(int x, int y) const {
    // Vérification des limites de la carte
    if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT) {
        return true; // Hors limites = mur
    }

    char cell = mapGrid[y][x];
    // '#' est un mur, tout le reste est traversable ('.', 'o', ' ', etc.)
    // Attention : ' ' (espace) peut être un tunnel ou une zone vide traversable
    return cell == '#';
}

int Map::tryEat(int x, int y) {
    // Vérification des limites
    if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT) {
        return 0;
    }

    char cell = mapGrid[y][x];

    if (cell == '.') {
        mapGrid[y][x] = ' '; // On vide la case
        return 10; // Score pour une pastille normale
    }
    else if (cell == 'o') {
        mapGrid[y][x] = ' '; // On vide la case
        return 50; // Score pour une super-pastille
    }

    return 0; // Rien à manger
}