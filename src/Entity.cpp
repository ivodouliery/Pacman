#include "../include/Entity.hpp"

#include <cmath>

Entity::Entity()
    : position(0.f, 0.f), direction(0.f, 0.f), nextDirection(0.f, 0.f), speed(0.f), animationTimer(0.0f), currentFrame(0), nbFrames(4), sprite_body(texture) {
}

void Entity::setPosition(float x, float y) {
    position = {x, y};
    // Align visual sprite to center of cell immediately
    sprite_body.setOrigin({entitySize / 2.0f, entitySize / 2.0f});
    sprite_body.setPosition(position + sf::Vector2f(cellSize / 2.0f, cellSize / 2.0f));
}

sf::Vector2f Entity::getPosition() const {
    return position;
}


bool Entity::canMove(const std::vector<std::string>& map, float x, float y) {
    // Calcul de la case de la grille avec floor pour gérer les négatifs correctement
    int gridX = static_cast<int>(std::floor((x - 16) / cellSize));
    int gridY = static_cast<int>(std::floor((y - 112) / cellSize));

    // Vérification des limites
    if (gridX < 0 || gridX >= 28 || gridY < 0 || gridY >= 30) {
        return false;
    }

    // Vérification du mur
    return map[gridY][gridX] != '#';
}

void Entity::alignToGrid() {
    // Snap to the center of the current cell on the perpendicular axis
    // If moving horizontally, snap Y. If moving vertically, snap X.
    
    // Logic position is top-left.
    // Center of cell is Logic + 8.
    // We want Logic to be exactly N * 16 + Origin.
    
    // Constant grid origin
    constexpr int gridOriginX = 16;
    constexpr int gridOriginY = 112;

    if (std::abs(direction.x) > 0) {
        // Moving Horizontal: Snap Y
        int gridY = std::round((position.y - gridOriginY) / cellSize);
        position.y = gridOriginY + gridY * cellSize;
    } else if (std::abs(direction.y) > 0) {
        // Moving Vertical: Snap X
        int gridX = std::round((position.x - gridOriginX) / cellSize);
        position.x = gridOriginX + gridX * cellSize;
    }
}

void Entity::update(float dt, const std::vector<std::string>& map) {
    // 1. Try to apply nextDirection if available
    if (nextDirection != sf::Vector2f(0.f, 0.f)) {
        // Check if we can turn
        // To turn, we must be close to the center? 
        // Or simply: is the target tile free?
        
        // We simulate a step in nextDirection from the SNAPPED position
        // This ensures that if we are 1px off, we check the correct tile
        
        // Temporarily calculate where we would be if we snapped
        sf::Vector2f snapPos = position;
        constexpr int gridOriginX = 16;
        constexpr int gridOriginY = 112;
        
        if (std::abs(nextDirection.x) > 0) {
            int gridY = std::round((snapPos.y - gridOriginY) / cellSize);
            snapPos.y = gridOriginY + gridY * cellSize;
        } else if (std::abs(nextDirection.y) > 0) {
            int gridX = std::round((snapPos.x - gridOriginX) / cellSize);
            snapPos.x = gridOriginX + gridX * cellSize;
        }
        
        // Check validity in that direction
        // We must check the ADJACENT tile, not the current one.
        // Current logic: snapPos is Top-Left of current cell.
        // Center is snapPos + 8.
        // Adjacent center is snapPos + 8 + 16 * dir.
        float centerX = snapPos.x + cellSize / 2.0f;
        float centerY = snapPos.y + cellSize / 2.0f;
        
        float checkX = centerX + nextDirection.x * cellSize;
        float checkY = centerY + nextDirection.y * cellSize;

        // Note: we also need to be reasonably close to the center to "snap" into the turn
        // otherwise we might snap from far away.
        // Let's check distance to snap center
        float dist = 0.f;
        if (std::abs(nextDirection.x) > 0) dist = std::abs(position.y - snapPos.y);
        else dist = std::abs(position.x - snapPos.x);

        // Allow turn if valid AND we are close enough to center
        // Relaxed tolerance to 4.0f to ensure turns are caught easily at high speed
        bool closeToCenter = dist < 4.0f;

        if (canMove(map, checkX, checkY) && closeToCenter) {
            direction = nextDirection;
            nextDirection = {0.f, 0.f};
            alignToGrid(); // Snap effectively
        }
    }

    if (direction == sf::Vector2f(0.f, 0.f)) return;

    // Apply Snapping (maintain alignment)
    alignToGrid();

    // Tunnel Teleportation
    int currentGridY = static_cast<int>(std::floor((position.y - 112) / cellSize));
    if (currentGridY >= 0 && currentGridY < static_cast<int>(map.size())) {
        // Check if this row is a tunnel (edges are empty)
        if (!map[currentGridY].empty() && map[currentGridY][0] == ' ') { 
             int currentGridX = static_cast<int>(std::round((position.x - 16) / cellSize));
             int mapWidth = static_cast<int>(map[0].length());
             
             if (direction.x < 0 && currentGridX <= 0) {
                 position.x = 16 + (mapWidth - 1) * cellSize;
             } else if (direction.x > 0 && currentGridX >= mapWidth - 1) {
                 position.x = 16;
             }
        }
    }

    sf::Vector2f nextPos = position + direction * speed * dt;

    // Check collision with 2 corners to prevent clipping
    float boxSize = cellSize; // 16 pixels
    // Margin defines the hitbox size. 
    // margin=4 means we check a box inset by 4px (8x8 pixel core).
    // This allows overlapping walls by 4px visually provided the core is safe.
    // Ideally margin=1 for tight 14x14 box. Let's try margin=2 (12x12 strictness).
    float margin = 2.0f; 
    
    sf::Vector2f check1;
    sf::Vector2f check2;

    if (direction.x > 0) { // Right
        // Leading edge: Right side of hitbox 
        // We look slightly ahead? Let's check exactly the new position's hitbox.
        // If we want to allow touching the wall but not entering:
        // We shouldn't check inside the wall.
        // Map walls are full 16x16 blocks.
        // If hitbox right edge is > wall left edge, collision.
        float leadX = nextPos.x + boxSize - margin; // 14
        check1 = {leadX, nextPos.y + margin};              
        check2 = {leadX, nextPos.y + boxSize - margin};    
    } else if (direction.x < 0) { // Left
        // Leading edge: Left side of hitbox
        float leadX = nextPos.x + margin; // 2
        check1 = {leadX, nextPos.y + margin};              
        check2 = {leadX, nextPos.y + boxSize - margin};    
        
    } else if (direction.y > 0) { // Down
        float leadY = nextPos.y + boxSize - margin;
        check1 = {nextPos.x + margin, leadY};              
        check2 = {nextPos.x + boxSize - margin, leadY};   
        
    } else if (direction.y < 0) { // Up
        float leadY = nextPos.y + margin;
        check1 = {nextPos.x + margin, leadY};              
        check2 = {nextPos.x + boxSize - margin, leadY};    
    }

    if (canMove(map, check1.x, check1.y) && canMove(map, check2.x, check2.y)) {
        position = nextPos;
    } else {
        alignToGrid();
    }
    
    // Sync visual
    sprite_body.setOrigin({entitySize / 2.0f, entitySize / 2.0f});
    sprite_body.setPosition(position + sf::Vector2f(cellSize / 2.0f, cellSize / 2.0f));
}

void Entity::setSpeed(float speed) {
    this->speed = speed;
}

float Entity::getSpeed() const {
    return speed;
}

void Entity::setDirection(sf::Vector2f direction) {
    this->direction = direction;
}

sf::Vector2f Entity::getDirection() const {
    return direction;
}

void Entity::setNextDirection(sf::Vector2f direction) {
    this->nextDirection = direction;
}

sf::Vector2f Entity::getNextDirection() const {
    return nextDirection;
}
