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
        "     #.## ######## ##.#     ",
        "######.## ######## ##.######", 
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
    window.draw(mapSprite);
    if (!started) return;
    for (int y = 0; y < MAP_HEIGHT; ++y) {
        for (int x = 0; x < MAP_WIDTH; ++x) {
            float posX = gridOriginX + x * Entity::cellSize;
            float posY = gridOriginY + y * Entity::cellSize;
            char cell = mapGrid[y][x];

            switch(cell) {
                case '.':
                    dotSprite.setPosition({posX, posY});
                    window.draw(dotSprite);
                    break;
                case 'o':
                    superDotSprite.setPosition({posX, posY});
                    window.draw(superDotSprite);
                    break;
                case 'B':
                    blinky.draw(window);
                    break;
                case 'P':
                    pinky.draw(window);
                    break;
                case 'I':
                    inky.draw(window);
                    break;
                case 'C':
                    clyde.draw(window);
                    break;
                case 'p':
                    pacman.draw(window);
                    break;
            }
        }
    }
}

void Map::update() {
    float dt = 1.0f / 60.0f; // Delta time fixe pour l'instant
    pacman.update(dt, mapGrid);
    blinky.update(dt, mapGrid);
    pinky.update(dt, mapGrid);
    inky.update(dt, mapGrid);
    clyde.update(dt, mapGrid);
}

void Map::handleInput(sf::Keyboard::Key key) {
    switch (key) {
        case sf::Keyboard::Key::Up:
            pacman.setNextDirection({0.f, -1.f});
            break;
        case sf::Keyboard::Key::Down:
            pacman.setNextDirection({0.f, 1.f});
            break;
        case sf::Keyboard::Key::Left:
            pacman.setNextDirection({-1.f, 0.f});
            break;
        case sf::Keyboard::Key::Right:
            pacman.setNextDirection({1.f, 0.f});
            break;
        default:
            break;
    }
}

void Map::start() {
    started = true;
    mapSprite = sf::Sprite(mapTexture);
}

