#pragma once
#include <SFML/Graphics.hpp>

/**
 * @file Entity.hpp
 * @brief Définition de la classe de base pour les entités du jeu.
 * 
 * Ce fichier contient la classe abstraite Entity, dont héritent Pacman et les Fantômes.
 * Elle gère les propriétés communes comme la position, la vitesse, la direction et l'animation.
 */

/**
 * @class Entity
 * @brief Classe de base abstraite pour toutes les entités mouvantes du jeu.
 * 
 * La classe Entity fournit les fonctionnalités de base pour le mouvement,
 * la gestion des collisions avec la grille, et l'affichage des sprites animés.
 */
class Entity {
public:
    /**
     * @brief Constructeur par défaut.
     * 
     * Initialise les variables membres (position, vitesse, direction) à zéro.
     */
    Entity();

    /**
     * @brief Taille d'une entité dans la texture (32x32 pixels).
     */
    static constexpr int entitySize = 32;

    /**
     * @brief Taille d'une case de la grille (16x16 pixels).
     */
    static constexpr float cellSize = 16.0f;

    /**
     * @brief Taille des yeux des fantômes (16x16 pixels).
     */
    static constexpr int eyesSize = 16;

    /**
     * @brief Durée d'affichage de chaque frame d'animation (en secondes).
     */
    static constexpr float animationSpeed = 0.1f;

    /**
     * @brief Destructeur virtuel par défaut.
     */
    virtual ~Entity() = default;

    /**
     * @brief Définit la position de l'entité.
     * 
     * @param x Coordonnée X en pixels.
     * @param y Coordonnée Y en pixels.
     */
    virtual void setPosition(float x, float y);

    /**
     * @brief Récupère la position actuelle de l'entité.
     * @return Un vecteur 2D contenant les coordonnées (x, y).
     */
    sf::Vector2f getPosition() const;

    /**
     * @brief Méthode virtuelle pure pour dessiner l'entité.
     * 
     * Doit être implémentée par les classes dérivées (Pacman, Ghost).
     * @param window La fenêtre de rendu SFML.
     */
    virtual void draw(sf::RenderWindow& window) = 0;

    /**
     * @brief Met à jour l'état de l'entité.
     * 
     * Gère le mouvement basé sur la vitesse et la direction, ainsi que l'animation.
     * @param dt Temps écoulé depuis la dernière frame (Delta Time).
     * @param map Référence à la grille du niveau pour les collisions.
     */
    virtual void update(float dt, const std::vector<std::string>& map);

    /**
     * @brief Définit la vitesse de déplacement.
     * @param speed Vitesse en pixels par seconde.
     */
    void setSpeed(float speed);

    /**
     * @brief Récupère la vitesse actuelle.
     * @return La vitesse en pixels par seconde.
     */
    float getSpeed() const;

    /**
     * @brief Définit la direction actuelle du mouvement.
     * @param direction Vecteur unitaire de direction (ex: {1, 0} pour droite).
     */
    void setDirection(sf::Vector2f direction);

    /**
     * @brief Récupère la direction actuelle.
     * @return Le vecteur de direction.
     */
    sf::Vector2f getDirection() const;

    /**
     * @brief Définit la prochaine direction souhaitée (buffer input).
     * @param direction Vecteur unitaire de la prochaine direction.
     */
    void setNextDirection(sf::Vector2f direction);

    /**
     * @brief Récupère la prochaine direction souhaitée.
     * @return Le vecteur de la prochaine direction.
     */
    sf::Vector2f getNextDirection() const;

    /**
     * @brief Vérifie si un mouvement est possible vers une position donnée.
     * 
     * @param map La grille du niveau.
     * @param x Coordonnée X cible.
     * @param y Coordonnée Y cible.
     * @return true si la case est libre (pas un mur), false sinon.
     */
    virtual bool canMove(const std::vector<std::string>& map, float x, float y);

    /**
     * @brief Aligne la position de l'entité sur la grille.
     * 
     * Permet de corriger les légers décalages lors des changements de direction
     * pour que l'entité reste parfaitement centrée dans les couloirs.
     */
    void alignToGrid();

protected:
    /**
     * @brief Position actuelle de l'entité (coin haut-gauche).
     */
    sf::Vector2f position;

    /**
     * @brief Direction actuelle du mouvement.
     */
    sf::Vector2f direction;

    /**
     * @brief Prochaine direction demandée par l'utilisateur ou l'IA.
     */
    sf::Vector2f nextDirection;

    /**
     * @brief Vitesse de déplacement en pixels/seconde.
     */
    float speed;
    
    /**
     * @brief Index de la frame d'animation actuelle.
     */
    int currentFrame;

    /**
     * @brief Timer accumulant le temps pour gérer le changement de frame.
     */
    float animationTimer;

    /**
     * @brief Nombre total de frames dans l'animation.
     */
    int nbFrames;

    /**
     * @brief Texture partagée ou spécifique de l'entité.
     */
    sf::Texture texture;

    /**
     * @brief Sprite principal représentant le corps de l'entité.
     */
    sf::Sprite sprite_body;

    /**
     * @brief Rectangle de texture définissant la zone à afficher.
     */
    sf::IntRect textureRect;
};
