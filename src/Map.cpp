#include "../include/Map.hpp"
#include <filesystem>
#include <iostream>

Map::Map(): blinky(GhostType::BLINKY), pinky(GhostType::PINKY), inky(GhostType::INKY), clyde(GhostType::CLYDE), pacman(), mapSprite(mapTexture), dotSprite(itemTexture), superDotSprite(itemTexture), m_font(), m_lblScore(m_font), m_txtScore(m_font), m_lblHighScore(m_font), m_txtHighScore(m_font) {
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

    // Initialize UI
    if (!m_font.openFromFile("assets/emulogic.ttf")) {
        // Try fallback
        if (!m_font.openFromFile("assets/font.ttf")) {
             std::cerr << "Warning: No font found (assets/emulogic.ttf or assets/font.ttf)" << std::endl;
        }
    }

    m_lblScore.setFont(m_font);
    m_lblScore.setString("Your Score");
    m_lblScore.setCharacterSize(22);
    m_lblScore.setFillColor(sf::Color::White);
    m_lblScore.setPosition(sf::Vector2f(35.f, 30.f));

    m_txtScore.setFont(m_font);
    m_txtScore.setString("0");
    m_txtScore.setCharacterSize(22);
    m_txtScore.setFillColor(sf::Color::White);
    m_txtScore.setPosition(sf::Vector2f(35.f, 50.f));

    m_lblHighScore.setFont(m_font);
    m_lblHighScore.setString("High Score");
    m_lblHighScore.setCharacterSize(22);
    m_lblHighScore.setFillColor(sf::Color::White);
    m_lblHighScore.setPosition(sf::Vector2f(250.f, 30.f));

    m_txtHighScore.setFont(m_font);
    m_txtHighScore.setString("0"); 
    m_txtHighScore.setCharacterSize(22);
    m_txtHighScore.setFillColor(sf::Color::White);
    m_txtHighScore.setPosition(sf::Vector2f(250.f, 50.f));
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
                default:
                    break;
            }
        }
    }

    // Draw Entities (Always on top of map elements)
    pacman.draw(window);
    blinky.draw(window);
    pinky.draw(window);
    inky.draw(window);
    clyde.draw(window);

    // Draw UI
    window.draw(m_lblScore);
    window.draw(m_txtScore);
    window.draw(m_lblHighScore);
    window.draw(m_txtHighScore);
}

void Map::update() {

    // Pellet Interaction
    sf::Vector2f pos = pacman.getPosition();
    // Calculate center of Pacman (logic is top-left)
    float centerX = pos.x + 8.0f; 
    float centerY = pos.y + 8.0f;
    
    int gridX = static_cast<int>((centerX - gridOriginX) / itemSize);
    int gridY = static_cast<int>((centerY - gridOriginY) / itemSize);
    
    if (gridX >= 0 && gridX < MAP_WIDTH && gridY >= 0 && gridY < MAP_HEIGHT) {
        char cell = mapGrid[gridY][gridX];
        if (cell == '.') {
            mapGrid[gridY][gridX] = ' ';
            m_score += 10;
            m_txtScore.setString(std::to_string(m_score));
        } else if (cell == 'o') {
            mapGrid[gridY][gridX] = ' ';
            m_score += 50;
            m_txtScore.setString(std::to_string(m_score));
            // TODO: Trigger frightened mode
        }
    }

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

