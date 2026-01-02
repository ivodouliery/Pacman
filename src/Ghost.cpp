#include "../include/Ghost.hpp"
#include <cmath>
#include <cstdlib> // For rand()
#include <queue>
#include <vector>

Ghost::Ghost(GhostType type) : type(type), mode(GhostMode::CHASE), sprite_eyes(texture), sprite_eyes_left_right(texture), sprite_eyes_up(texture), sprite_eyes_down(texture), sprite_body_dead(texture), lastGridPos(-1, -1) {
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

void Ghost::update(float dt, const std::vector<std::string>& map, sf::Vector2f pacmanPos) {
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
                 float homeX = 16 + 13 * cellSize + 8.0f;
                 float homeY = 112 + 14 * cellSize; 
                 sf::Vector2f target = {homeX, homeY};
                 
                 sf::Vector2f bestDir = getBestDirectionForTarget(target, possibleDirs, map);

                 if (direction == sf::Vector2f(0.f, 0.f)) setDirection(bestDir);
                 else setNextDirection(bestDir);

            } else if (mode == GhostMode::CHASE) {
                // Chase Pacman
                sf::Vector2f bestDir = getBestDirectionForTarget(pacmanPos, possibleDirs, map);
                
                if (direction == sf::Vector2f(0.f, 0.f)) setDirection(bestDir);
                else setNextDirection(bestDir);
            } else {
                // SCATTER (random for now) or FRIGHTENED (random)
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

sf::Vector2f Ghost::getBestDirectionForTarget(sf::Vector2f target, const std::vector<sf::Vector2f>& possibleDirs, const std::vector<std::string>& map) {
    if (possibleDirs.empty()) return {0,0};

    // BFS setup
    int targetGridX = static_cast<int>(std::floor((target.x - 16) / cellSize));
    int targetGridY = static_cast<int>(std::floor((target.y - 112) / cellSize));
    
    // Bounds check
    if (targetGridX < 0) targetGridX = 0;
    if (targetGridX >= 28) targetGridX = 27;
    if (targetGridY < 0) targetGridY = 0;
    if (targetGridY >= 31) targetGridY = 30;

    // Distance map (initialized to -1)
    std::vector<std::vector<int>> distMap(35, std::vector<int>(30, -1));
    std::queue<sf::Vector2i> q;

    q.push({targetGridX, targetGridY});
    distMap[targetGridY][targetGridX] = 0;
    
    // Run BFS backwards from Target to everywhere
    while(!q.empty()) {
        sf::Vector2i curr = q.front();
        q.pop();
        
        sf::Vector2i dirs[] = {{0,1}, {0,-1}, {1,0}, {-1,0}};
        for(auto d : dirs) {
            int nx = curr.x + d.x;
            int ny = curr.y + d.y;
            
            // Check bounds (0-27, 0-30)
            if (nx >= 0 && nx < 28 && ny >= 0 && ny < 31) {
                // Check wall
                if (map[ny][nx] != '#' && distMap[ny][nx] == -1) {
                    distMap[ny][nx] = distMap[curr.y][curr.x] + 1;
                    q.push({nx, ny});
                }
            }
        }
    }

    // Now check which neighbor has the smallest distance
    sf::Vector2f bestDir = possibleDirs[0];
    int minDist = 999999;
    
    int currentGridX = static_cast<int>(std::floor((position.x - 16) / cellSize));
    int currentGridY = static_cast<int>(std::floor((position.y - 112) / cellSize));

    for(const auto& d : possibleDirs) {
        int nx = currentGridX + static_cast<int>(d.x);
        int ny = currentGridY + static_cast<int>(d.y);
        
        if (nx >= 0 && nx < 28 && ny >= 0 && ny < 31) {
             int dVal = distMap[ny][nx];
             if (dVal != -1 && dVal < minDist) {
                 minDist = dVal;
                 bestDir = d;
             }
        }
    }
    
    return bestDir;
}
