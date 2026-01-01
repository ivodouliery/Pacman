#include "../include/Entity.hpp"

Entity::Entity()
    : position(0.f, 0.f), direction(0.f, 0.f), speed(0.f), animationTimer(0.0f), currentFrame(0), nbFrames(4), sprite_body(texture) {
}

void Entity::setPosition(float x, float y) {
    position = {x, y - cellSize / 2.0f};
    sprite_body.setPosition(position);
}

sf::Vector2f Entity::getPosition() const {
    return position;
}


bool Entity::canMove(const std::vector<std::string>& map, float x, float y) {
    // Calcul de la case de la grille
    int gridX = static_cast<int>((x - 16) / cellSize);
    int gridY = static_cast<int>((y - 112) / cellSize);

    // Vérification des limites
    if (gridX < 0 || gridX >= 28 || gridY < 0 || gridY >= 30) {
        return false;
    }

    // Vérification du mur
    return map[gridY][gridX] != '#';
}

void Entity::update(float dt, const std::vector<std::string>& map) {
    sf::Vector2f nextPos = position + direction * speed * dt;

    // On vérifie le point central "futur"
    // Note: Pour faire ça parfaitement il faudrait vérifier les coins ou le point devant
    // Pour l'instant on reprend ton idée de vérifier si la case est disponible
    
    // Position du "devant" de l'entité pour anticiper le mur
    float checkX = nextPos.x;
    float checkY = nextPos.y;
    float offset = cellSize / 2.0f; // 8 pixels

    if (direction.x > 0) checkX += offset;       
    else if (direction.x < 0) checkX -= offset; 
    if (direction.y > 0) checkY += offset;       
    else if (direction.y < 0) checkY -= offset;  

    if (canMove(map, checkX, checkY)) {
        position = nextPos;
    } else {
        // Optionnel : On peut s'aligner parfaitement à la grille ici pour éviter de "vibrer" contre le mur
        // Mais simplement ne pas bouger suffit pour arrêter le mouvement
    }
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
