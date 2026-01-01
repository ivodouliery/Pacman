#include "../include/Map.hpp"
#include <filesystem>
#include <iostream>

Map::Map(): blinky(GhostType::BLINKY), pinky(GhostType::PINKY), inky(GhostType::INKY), clyde(GhostType::CLYDE), pacman(), mapSprite(mapTexture), dotSprite(itemTexture), superDotSprite(itemTexture), m_font(), m_lblScore(m_font), m_txtScore(m_font), m_lblHighScore(m_font), m_txtHighScore(m_font), m_lifeSprite(itemTexture) {
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
    resetPositions();

    if (!m_font.openFromFile("assets/font.ttf")) {
        std::cerr << "Warning: No font found (assets/font.ttf)" << std::endl;
    }
}

void Map::resetPositions() {
    m_ghostsActive = false;
    for (int y = 0; y < MAP_HEIGHT; ++y) {
        for (int x = 0; x < MAP_WIDTH; ++x) {
            float posX = gridOriginX + x * Entity::cellSize;
            float posY = gridOriginY + y * Entity::cellSize;
            char cell = mapGrid[y][x];
            
            switch(cell) {
                case 'p':
                    pacman.setPosition(posX, posY);
                    pacman.setDirection({0.f, 0.f});
                    pacman.setNextDirection({0.f, 0.f});
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
    

    m_lblScore.setFont(m_font);
    m_lblScore.setString("Your Score");
    m_lblScore.setCharacterSize(25); // Slightly smaller to match target look better? Or keep 22. User set 22.
    m_lblScore.setFillColor(sf::Color::White);
    m_lblScore.setPosition(sf::Vector2f(30.f, 25.f));

    m_txtScore.setFont(m_font);
    m_txtScore.setString("0");
    m_txtScore.setCharacterSize(25);
    m_txtScore.setFillColor(sf::Color::White);
    m_txtScore.setPosition(sf::Vector2f(30.f, 55.f));

    m_lblHighScore.setFont(m_font);
    m_lblHighScore.setString("High Score");
    m_lblHighScore.setCharacterSize(25);
    m_lblHighScore.setFillColor(sf::Color::White);
    m_lblHighScore.setPosition(sf::Vector2f(270.f, 25.f));

    m_txtHighScore.setFont(m_font);
    m_txtHighScore.setString("0"); 
    m_txtHighScore.setCharacterSize(25);
    m_txtHighScore.setFillColor(sf::Color::White);
    m_txtHighScore.setPosition(sf::Vector2f(270.f, 55.f));

    // Life Sprite Init
    static sf::Texture pacTexture;
    if (pacTexture.getSize().x == 0) {
        if (!pacTexture.loadFromFile("./assets/pacman.png")) { 
             std::cerr << "Warning: Could not load assets/pacman.png for UI" << std::endl;
        }
    }
    m_lifeSprite.setTexture(pacTexture);
    // Use the "left" facing or "neutral" frame. 
    // Pacman.cpp uses {1*entitySize, 0} as start? Or {0,0}?
    // Let's use 1st frame: {0, 0, 16, 16}
    m_lifeSprite.setTextureRect(sf::IntRect({1*Entity::entitySize, 0}, {Entity::entitySize, Entity::entitySize})); 
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

    // Draw Lives
    int lives = pacman.getLives();
    // Assuming icons at bottom left, e.g. (30, MAP_HEIGHT*16 + 10)
    // Or closer to standard position
    float startX = 48.0f;
    float startY = 592.0f;
    
    for (int i = 0; i < lives; ++i) {
        m_lifeSprite.setPosition(sf::Vector2f(startX + i * Entity::entitySize, startY));
        window.draw(m_lifeSprite);
    }
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

    // Check if we should activate ghosts
    if (!m_ghostsActive) {
        if (pacman.getDirection() != sf::Vector2f(0.f, 0.f)) {
            m_ghostsActive = true;
        }
    }

    if (m_ghostsActive) {
        blinky.update(dt, mapGrid);
        pinky.update(dt, mapGrid);
        inky.update(dt, mapGrid);
        clyde.update(dt, mapGrid);
    }

    // Collision Detection
    // Check collision with ghosts
    // Simple distance check (e.g. < 10 pixels seems generous enough for hit)
    std::vector<Ghost*> ghosts = {&blinky, &pinky, &inky, &clyde};
    sf::Vector2f pacPos = pacman.getPosition();
    // Center point
    sf::Vector2f pacCenter = pacPos + sf::Vector2f(8.f, 8.f);

    for (auto* ghost : ghosts) {
        sf::Vector2f ghostPos = ghost->getPosition();
        sf::Vector2f ghostCenter = ghostPos + sf::Vector2f(8.f, 8.f);
        
        float dx = pacCenter.x - ghostCenter.x;
        float dy = pacCenter.y - ghostCenter.y;
        float distSq = dx*dx + dy*dy;
        
        // Threshold: 8 pixels radius sum? 16*16 = 256. 
        // Let's go strict: 10*10 = 100
        if (distSq < 100.0f) {
            // Collision!
            // TODO: Check for Frightened Mode
            if (true) { // Normal mode
                 pacman.removeLife();
                 if (pacman.getLives() >= 0) {
                     resetPositions();
                     // Maybe reset game state or pause?
                 } else {
                     // Game Over logic (not requested yet, but stop game?)
                     started = false; 
                     // Or screen change
                 }
            }
        }
    }

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

