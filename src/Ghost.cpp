#include "../include/Ghost.hpp"
#include <cmath>
#include <cstdlib> // For rand()

Ghost::Ghost(GhostType type) : type(type), mode(GhostMode::SCATTER), sprite_eyes(texture), sprite_eyes_left_right(texture), sprite_eyes_up(texture), sprite_eyes_down(texture), sprite_body_dead(texture), lastGridPos(-1, -1) {
    speed = 90.0f; // Slightly slower than Pacman
    if(!texture.loadFromFile("./assets/ghosts.png")) {
        throw std::runtime_error("Failed to load texture");
    }
    sprite_body = sf::Sprite(texture);

    sprite_eyes_up.setTextureRect(sf::IntRect({5*eyesSize, eyesOriginY}, {eyesSize, eyesSize}));
    sprite_eyes_down.setTextureRect(sf::IntRect({6*eyesSize, eyesOriginY}, {eyesSize, eyesSize}));

    switch(type) {
        case GhostType::BLINKY: 
            sprite_body.setTextureRect(sf::IntRect({0*entitySize, 0*entitySize}, {entitySize, entitySize}));
            sprite_eyes_left_right.setTextureRect(sf::IntRect({0*eyesSize, eyesOriginY}, {eyesSize, eyesSize}));
            sprite_body_dead.setTextureRect(sf::IntRect({0, eyesOriginY + eyesSize}, {eyesSize, eyesSize}));
            sprite_eyes = sprite_eyes_left_right;
            break;
        case GhostType::INKY: 
            sprite_body.setTextureRect(sf::IntRect({0*entitySize, 1*entitySize}, {entitySize, entitySize}));
            sprite_eyes_left_right.setTextureRect(sf::IntRect({1*eyesSize, eyesOriginY}, {eyesSize, eyesSize}));
            sprite_body_dead.setTextureRect(sf::IntRect({1*eyesSize, eyesOriginY + eyesSize}, {eyesSize, eyesSize}));
            sprite_eyes = sprite_eyes_left_right;
            break;
        case GhostType::PINKY: 
            sprite_body.setTextureRect(sf::IntRect({0*entitySize, 2*entitySize}, {entitySize, entitySize}));
            sprite_eyes_left_right.setTextureRect(sf::IntRect({2*eyesSize, eyesOriginY}, {eyesSize, eyesSize}));
            sprite_body_dead.setTextureRect(sf::IntRect({2*eyesSize, eyesOriginY + eyesSize}, {eyesSize, eyesSize}));
            sprite_eyes = sprite_eyes_left_right;
            break;
        case GhostType::CLYDE: 
            sprite_body.setTextureRect(sf::IntRect({0*entitySize, 3*entitySize}, {entitySize, entitySize}));
            sprite_eyes_left_right.setTextureRect(sf::IntRect({3*eyesSize, eyesOriginY}, {eyesSize, eyesSize}));
            sprite_body_dead.setTextureRect(sf::IntRect({3*eyesSize, eyesOriginY + eyesSize}, {eyesSize, eyesSize}));
            sprite_eyes = sprite_eyes_left_right;
            break;
    }

}


void Ghost::setPosition(float x, float y) {
    Entity::setPosition(x, y);
    sf::Vector2f center = position + sf::Vector2f(cellSize / 2.0f, cellSize / 2.0f);
    sprite_eyes.setPosition(center);
    sprite_eyes.setOrigin({eyesSize / 2.0f, eyesSize / 2.0f});
    sprite_body_dead.setPosition(center);
    sprite_body_dead.setOrigin({eyesSize / 2.0f, eyesSize / 2.0f});
}

void Ghost::draw(sf::RenderWindow& window) {
    if (mode == GhostMode::DEAD) {
        window.draw(sprite_body_dead);
    } else {
        window.draw(sprite_body);
        window.draw(sprite_eyes);
    }
}

void Ghost::update(float dt, const std::vector<std::string>& map) {
    // Speed Handling
    if (mode == GhostMode::DEAD) {
        speed = 200.0f;
    } else if (mode == GhostMode::FRIGHTENED) {
        speed = 50.0f; // Slower when frightened
    } else {
        speed = 90.0f; // Normal
    }

    // Determine current grid cell
    int gridX = static_cast<int>(std::floor((position.x - 16) / cellSize));
    int gridY = static_cast<int>(std::floor((position.y - 112) / cellSize));

    // Check if reached home (DEAD mode)
    if (mode == GhostMode::DEAD) {
        float homeX = 16 + 13 * cellSize + 8.0f;
        float homeY = 112 + 10 * cellSize;
        
        float dx = position.x - homeX;
        float dy = position.y - homeY;
        if (dx*dx + dy*dy < 100.0f) { // Close enough
            mode = GhostMode::CHASE; // Revived!
            speed = 90.0f;
        }
    }

    // Decision making: only when entering a new tile or stopped
    if (gridX != lastGridPos.x || gridY != lastGridPos.y || direction == sf::Vector2f(0.f, 0.f)) {
        lastGridPos = {gridX, gridY};

        std::vector<sf::Vector2f> possibleDirs;
        sf::Vector2f dirs[] = { {0, -1}, {0, 1}, {-1, 0}, {1, 0} }; // Up, Down, Left, Right

        for (const auto& d : dirs) {
            float centerX = (gridX * cellSize + 16) + cellSize / 2.0f;
            float centerY = (gridY * cellSize + 112) + cellSize / 2.0f;
            float checkX = centerX + d.x * cellSize;
            float checkY = centerY + d.y * cellSize;

            if (canMove(map, checkX, checkY)) {
                // Don't reverse direction (unless it's the only option or we are stopped)
                if (direction != sf::Vector2f(0.f, 0.f) && d == -direction) {
                    continue; 
                }
                possibleDirs.push_back(d);
            }
        }

        if (possibleDirs.empty() && direction != sf::Vector2f(0.f, 0.f)) {
             possibleDirs.push_back(-direction);
        }

        if (!possibleDirs.empty()) {
            if (mode == GhostMode::DEAD) {
                 // Target Finding Logic (A* simplified: Greedy Best First)
                 float homeX = 16 + 13 * cellSize + 8.0f;
                 float homeY = 112 + 10 * cellSize;
                 sf::Vector2f target = {homeX, homeY};
                 
                 sf::Vector2f bestDir = possibleDirs[0];
                 float minDistSq = 999999999.f;
                 
                 for(const auto& d : possibleDirs) {
                     sf::Vector2f nextTilePos = position + d * cellSize; // Approx
                     float dx = nextTilePos.x - target.x;
                     float dy = nextTilePos.y - target.y;
                     float distSq = dx*dx + dy*dy;
                     if (distSq < minDistSq) {
                         minDistSq = distSq;
                         bestDir = d;
                     }
                 }
                 setNextDirection(bestDir); // Buffer it? Or set directly?
                 if (direction == sf::Vector2f(0.f, 0.f)) setDirection(bestDir);
                 else setNextDirection(bestDir);

            } else {
                // Random (or Chase later)
                int idx = rand() % possibleDirs.size();
                if (direction == sf::Vector2f(0.f, 0.f)) {
                    setDirection(possibleDirs[idx]);
                } else {
                    setNextDirection(possibleDirs[idx]);
                }
            }
        }
    }

    Entity::update(dt, map);
    
    // Animation Update
    animationTimer += dt;
    if(animationTimer >= animationSpeed) {
        animationTimer -= animationSpeed;
        currentFrame = (currentFrame + 1) % nbFrames;
        if (mode == GhostMode::FRIGHTENED) {

            sprite_body.setTextureRect(sf::IntRect({(currentFrame % 2) * entitySize, 4*entitySize}, {entitySize, entitySize}));
        } else {
            switch(type) {
                case GhostType::BLINKY: 
                    sprite_body.setTextureRect(sf::IntRect({currentFrame * entitySize, 0*entitySize}, {entitySize, entitySize}));
                    break;
                case GhostType::INKY: 
                    sprite_body.setTextureRect(sf::IntRect({currentFrame * entitySize, 1*entitySize}, {entitySize, entitySize}));
                    break;
                case GhostType::PINKY: 
                    sprite_body.setTextureRect(sf::IntRect({currentFrame * entitySize, 2*entitySize}, {entitySize, entitySize}));
                    break;
                case GhostType::CLYDE: 
                    sprite_body.setTextureRect(sf::IntRect({currentFrame * entitySize, 3*entitySize}, {entitySize, entitySize}));
                    break;
            }
        }
    }

    // Align visual elements
    sf::Vector2f center = position + sf::Vector2f(cellSize / 2.0f, cellSize / 2.0f);
    sprite_eyes.setPosition(center);
    sprite_eyes.setOrigin({eyesSize / 2.0f, eyesSize / 2.0f});
    sprite_body_dead.setPosition(center);
    sprite_body_dead.setOrigin({eyesSize / 2.0f, eyesSize / 2.0f});
    

    if (direction.x > 0) setRotation(3); // Right
    else if (direction.x < 0) setRotation(2); // Left
    else if (direction.y < 0) setRotation(0); // Up
    else if (direction.y > 0) setRotation(1); // Down
}

void Ghost::setRotation(int direction) {
    // 0: Up, 1: Down, 2: Left, 3: Right
    switch(direction) {
        case 0: // Up
            sprite_eyes.setTextureRect(sprite_eyes_up.getTextureRect());
            break;
        case 1: // Down
            sprite_eyes.setTextureRect(sprite_eyes_down.getTextureRect());
            break;
        default: // Left/Right/Neutral
            sprite_eyes.setTextureRect(sprite_eyes_left_right.getTextureRect());
            break;
    }
}
