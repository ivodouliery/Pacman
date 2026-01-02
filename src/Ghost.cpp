#include "../include/Ghost.hpp"
#include <cmath>
#include <cstdlib> // For rand()
#include <queue>
#include <vector>

/**
 * @brief Constructeur de Ghost.
 * 
 * Initialise le fantôme selon son type (Blinky, Pinky, Inky, Clyde).
 * Configure les sprites (corps, yeux) et les textures correspondantes.
 * Définit la vitesse initiale et le mode par défaut (CHASE).
 * 
 * @param type Le type de fantôme à créer.
 * @throws std::runtime_error Si la texture "ghosts.png" ne peut pas être chargée.
 */
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


/**
 * @brief Définit la position du fantôme.
 * 
 * Met à jour la position de l'entité de base.
 * Centre les sprites des yeux et du corps "mort" sur la nouvelle position.
 * 
 * @param x Coordonnée X.
 * @param y Coordonnée Y.
 */
void Ghost::setPosition(float x, float y) {
    Entity::setPosition(x, y);
    sf::Vector2f center = position + sf::Vector2f(cellSize / 2.0f, cellSize / 2.0f);
    sprite_eyes.setPosition(center);
    sprite_eyes.setOrigin({eyesSize / 2.0f, eyesSize / 2.0f});
    sprite_body_dead.setPosition(center);
    sprite_body_dead.setOrigin({eyesSize / 2.0f, eyesSize / 2.0f});
}

/**
 * @brief Dessine le fantôme.
 * 
 * Si le fantôme est mort, dessine uniquement les yeux (ou le sprite de mort).
 * Sinon, dessine le corps puis les yeux par-dessus.
 * 
 * @param window La fenêtre de rendu.
 */
void Ghost::draw(sf::RenderWindow& window) {
    if (mode == GhostMode::DEAD) {
        window.draw(sprite_body_dead);
    } else {
        window.draw(sprite_body);
        window.draw(sprite_eyes);
    }
}

/**
 * @brief Met à jour l'IA et le mouvement du fantôme.
 * 
 * Gère :
 * 1. La vitesse en fonction du mode (Chase, Frightened, Dead).
 * 2. La détection de la case courante.
 * 3. Le retour à la base en mode DEAD (résurrection si atteint).
 * 4. La prise de décision aux intersections (choix de direction).
 *    - Utilise un algorithme BFS (via getBestDirectionForTarget) pour trouver le chemin le plus court vers la cible.
 *    - La cible dépend du type de fantôme et du mode (Chase/Scatter).
 *    - En mode Frightened, le mouvement est aléatoire.
 * 5. L'animation du sprite (mouvement des jambes/fantôme).
 * 6. L'orientation des yeux.
 * 
 * @param dt Temps écoulé.
 * @param map La grille du niveau.
 * @param pacmanPos La position de Pacman.
 */
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
                sf::Vector2f bestDir = {0,0};
                bool useRandom = false;

                if (type == GhostType::BLINKY) {
                    // Blinky: Always Chase using BFS
                    bestDir = getBestDirectionForTarget(pacmanPos, possibleDirs, map);

                } else if (type == GhostType::PINKY) {
                    // Pinky: Random
                    useRandom = true;

                } else if (type == GhostType::INKY) {
                    // Inky: Alternate Chase (20s) / Scatter-Random (7s)
                    strategyTimer += dt;
                    if (isChasing && strategyTimer > 20.0f) {
                        isChasing = false; 
                        strategyTimer = 0;
                    } else if (!isChasing && strategyTimer > 7.0f) {
                        isChasing = true; 
                        strategyTimer = 0;
                    }

                    if (isChasing) {
                        bestDir = getBestDirectionForTarget(pacmanPos, possibleDirs, map);
                    } else {
                        useRandom = true;
                    }
                } else if (type == GhostType::CLYDE) {
                    // Clyde: Alternate Chase (10s) / Scatter-Random (3s)
                    strategyTimer += dt;
                    if (isChasing && strategyTimer > 10.0f) {
                        isChasing = false; 
                        strategyTimer = 0;
                    } else if (!isChasing && strategyTimer > 3.0f) {
                        isChasing = true; 
                        strategyTimer = 0;
                    }

                    if (isChasing) {
                        bestDir = getBestDirectionForTarget(pacmanPos, possibleDirs, map);
                    } else {
                        useRandom = true;
                    }
                }

                if (useRandom) {
                     int idx = rand() % possibleDirs.size();
                     bestDir = possibleDirs[idx];
                }
                
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

/**
 * @brief Définit l'orientation des yeux du fantôme.
 * 
 * Change le rectangle de texture des yeux en fonction de la direction.
 * 
 * @param direction Entier représentant la direction (0: Haut, 1: Bas, 2: Gauche, 3: Droite).
 */
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

/**
 * @brief Calcule la meilleure direction pour atteindre une cible.
 * 
 * Utilise un algorithme BFS (Breadth-First Search) inversé partant de la cible
 * pour calculer la distance de chaque case à la cible.
 * Ensuite, choisit parmi les directions possibles celle qui mène à la case
 * ayant la plus petite distance vers la cible.
 * 
 * @param target La position cible (en pixels).
 * @param possibleDirs Liste des directions valides depuis la position actuelle.
 * @param map La grille du niveau.
 * @return sf::Vector2f La direction optimale (vecteur unitaire).
 */
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
