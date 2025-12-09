#include "../include/Map.hpp"

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
    sf::Texture gridTexture("./assets/.png");
    sf::Sprite gridSprite(gridTexture);
    gridSprite.setPosition({0, 0});
    window.draw(gridSprite);
    wall.setFillColor(sf::Color::Blue);



    for (size_t y = 0; y < map.size(); ++y) {
        for (size_t x = 0; x < map[y].size(); ++x) {
            if (map[y][x] == '.') {
                sf::Texture texture("./graphic_assets/other/dot.png");
                sf::Sprite sprite(texture);
                sprite.setPosition({x * cellSize, y * cellSize});
                window.draw(sprite);
            }
            else if (map[y][x] == 'P') {
                sf::Texture texture("./graphic_assets/pacman-left/1.png");
                sf::Sprite sprite(texture);
                sprite.setPosition({x * cellSize, y * cellSize});
                window.draw(sprite);
            }
            else if (map[y][x] == 'G') {
                sf::Texture texture("./graphic_assets/ghosts/blinky.png");
                sf::Sprite sprite(texture);
                sprite.setPosition({x * cellSize, y * cellSize});
                window.draw(sprite);
            }
        }
    }

}
