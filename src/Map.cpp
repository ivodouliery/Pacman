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
