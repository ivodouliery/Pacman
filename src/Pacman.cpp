#include "../include/Pacman.hpp"
#include <cmath>

/**
 * @brief Constructeur de Pacman.
 * 
 * Initialise la vitesse par défaut (100.0f).
 * Charge la texture "pacman.png".
 * Configure le sprite initial (bouche fermée ou semi-ouverte).
 * 
 * @throws std::runtime_error Si la texture ne peut pas être chargée.
 */
Pacman::Pacman() {
    speed = 100.0f; // Default speed
    if(!texture.loadFromFile("./assets/pacman.png")) {
        throw std::runtime_error("Failed to load texture");
    }
    sprite_body = sf::Sprite(texture);
    sprite_body.setTextureRect(sf::IntRect({1*entitySize, 0}, {entitySize, entitySize}));
}

/**
 * @brief Dessine Pacman.
 * 
 * @param window La fenêtre de rendu.
 */
void Pacman::draw(sf::RenderWindow& window) {
    window.draw(sprite_body);
}

/**
 * @brief Met à jour Pacman.
 * 
 * Appelle Entity::update pour le mouvement de base.
 * Gère l'animation de la bouche (cycle de frames).
 * Applique la rotation du sprite en fonction de la direction actuelle.
 * 
 * @param dt Temps écoulé.
 * @param map La grille du niveau.
 */
void Pacman::update(float dt, const std::vector<std::string>& map) {
    Entity::update(dt, map);
    animationTimer += dt;
    if (animationTimer >= animationSpeed) {
        animationTimer -= animationSpeed;
        currentFrame = (currentFrame + 1) % nbFrames;
        sprite_body.setTextureRect(sf::IntRect({currentFrame * entitySize, 0}, {entitySize, entitySize}));
    }
    
    // We only need to handle rotation here.
    if(direction == sf::Vector2f{1.f, 0.f}) {
        sprite_body.setRotation(sf::degrees(0.0f));
    } else if(direction == sf::Vector2f{-1.f, 0.f}) {
        sprite_body.setRotation(sf::degrees(180.0f));
    } else if(direction == sf::Vector2f{0.f, 1.f}) {
        sprite_body.setRotation(sf::degrees(90.0f));
    } else if(direction == sf::Vector2f{0.f, -1.f}) {
        sprite_body.setRotation(sf::degrees(-90.0f));
    }
}

/**
 * @brief Définit la position de Pacman.
 * 
 * Appelle simplement la méthode de base Entity::setPosition.
 * 
 * @param x Coordonnée X.
 * @param y Coordonnée Y.
 */
void Pacman::setPosition(float x, float y) {
    Entity::setPosition(x, y);
}

/**
 * @brief Vérifie si Pacman peut se déplacer.
 * 
 * Ajoute une règle spécifique : Pacman ne peut pas traverser les portes ('-').
 * 
 * @param map La grille du niveau.
 * @param x Coordonnée X cible.
 * @param y Coordonnée Y cible.
 * @return true si le mouvement est autorisé.
 */
bool Pacman::canMove(const std::vector<std::string>& map, float x, float y) {
    if (!Entity::canMove(map, x, y)) return false;

    int gridX = static_cast<int>(std::floor((x - 16) / cellSize));
    int gridY = static_cast<int>(std::floor((y - 112) / cellSize));
    
    return map[gridY][gridX] != '-';
}

