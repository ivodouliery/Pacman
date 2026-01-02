#pragma once
#include "Entity.hpp"
#include <vector>

/**
 * @file Ghost.hpp
 * @brief Définition de la classe Ghost et des énumérations associées.
 * 
 * Ce fichier contient la classe Ghost qui gère le comportement des ennemis (IA, états, affichage).
 */

/**
 * @enum GhostType
 * @brief Identifie les différents fantômes du jeu.
 */
enum class GhostType {
    BLINKY,  /**< Rouge - Le plus agressif, chasse directement Pac-Man (Shadow). */
    PINKY,   /**< Rose - Pathing aléatoire */
    INKY,    /**< Bleu - Alterne entre CHASE (20 sec) et SCATTER (7 sec) */
    CLYDE    /**< Orange - Alterne entre CHASE (10 sec) et SCATTER (3 sec) */
};

/**
 * @enum GhostMode
 * @brief Définit l'état comportemental actuel d'un fantôme.
 */
enum class GhostMode {
    CHASE,      /**< Poursuit Pac-Man selon sa stratégie propre. */
    SCATTER,    /**< Se dirige vers son coin assigné (mode dispersion). */
    FRIGHTENED, /**< Vulnérable (bleu foncé), se déplace lentement et aléatoirement. */
    DEAD        /**< Yeux seuls, retourne rapidement à la maison des fantômes pour revivre. */
};

/**
 * @class Ghost
 * @brief Classe représentant un fantôme ennemi.
 * 
 * Gère l'intelligence artificielle, les changements d'état (Chasse, Fuite, Mort)
 * et l'affichage des différentes parties du sprite (corps, yeux).
 */
class Ghost : public Entity {
public:
    /**
     * @brief Constructeur de Ghost.
     * 
     * @param type Le type de fantôme (Blinky, Pinky, Inky, Clyde) déterminant son apparence et son IA.
     */
    Ghost(GhostType type);

    /**
     * @brief Met à jour l'IA et le mouvement du fantôme.
     * 
     * Calcule la prochaine direction en fonction du mode actuel et de la position de Pac-Man.
     * 
     * @param dt Temps écoulé depuis la dernière frame.
     * @param map La grille du niveau.
     * @param pacmanPos La position actuelle de Pac-Man (cible).
     */
    void update(float dt, const std::vector<std::string>& map, sf::Vector2f pacmanPos);

    /**
     * @brief Dessine le fantôme sur la fenêtre.
     * 
     * Affiche le corps (ou les yeux seuls si mort) et gère l'animation.
     * 
     * @param window La fenêtre de rendu SFML.
     */
    void draw(sf::RenderWindow& window) override;

    /**
     * @brief Définit la position du fantôme.
     * 
     * Met également à jour la position des sprites secondaires (yeux).
     * 
     * @param x Coordonnée X.
     * @param y Coordonnée Y.
     */
    void setPosition(float x, float y) override;

    /**
     * @brief Oriente le regard du fantôme.
     * 
     * Change le sprite des yeux en fonction de la direction.
     * 
     * @param direction Entier représentant la direction (0: Haut, 1: Bas, 2: Gauche, 3: Droite).
     */
    void setRotation(int direction);

    /**
     * @brief Change le mode comportemental du fantôme.
     * @param m Le nouveau mode (CHASE, SCATTER, FRIGHTENED, DEAD).
     */
    void setMode(GhostMode m) { mode = m; }

    /**
     * @brief Récupère le mode actuel du fantôme.
     * @return Le mode actuel.
     */
    GhostMode getMode() const { return mode; }

    /**
     * @brief Position Y dans la texture pour les yeux.
     */
    static constexpr int eyesOriginY = 10*entitySize;
    
    // AI State
    /**
     * @brief Dernière position grille visitée (pour éviter les demi-tours immédiats).
     */
    sf::Vector2i lastGridPos;

    /**
     * @brief Timer pour gérer l'alternance des stratégies (Chase/Scatter).
     */
    float strategyTimer = 0.0f;

    /**
     * @brief Indique si le fantôme est en mode poursuite (true) ou dispersion (false).
     */
    bool isChasing = true;

private:
    /**
     * @brief Type du fantôme.
     */
    GhostType type;

    /**
     * @brief Mode actuel du fantôme.
     */
    GhostMode mode;

    /**
     * @brief Sprite des yeux (générique).
     */
    sf::Sprite sprite_eyes;

    /**
     * @brief Sprite des yeux regardant vers le haut.
     */
    sf::Sprite sprite_eyes_up;

    /**
     * @brief Sprite des yeux regardant vers le bas.
     */
    sf::Sprite sprite_eyes_down;   

    /**
     * @brief Sprite des yeux regardant vers la gauche ou la droite.
     */
    sf::Sprite sprite_eyes_left_right;

    /**
     * @brief Sprite du corps en mode mort (yeux seuls, ou score affiché).
     * Note: Dans cette implémentation, semble être utilisé pour les yeux seuls ou un état spécifique.
     */
    sf::Sprite sprite_body_dead;
    
    /**
     * @brief Calcule la meilleure direction pour atteindre une cible.
     * 
     * Utilise la distance euclidienne au carré pour choisir la direction qui minimise la distance à la cible.
     * 
     * @param target Position cible (en pixels).
     * @param possibleDirs Liste des directions valides (pas de mur).
     * @param map La grille du niveau.
     * @return Le vecteur de direction choisi.
     */
    sf::Vector2f getBestDirectionForTarget(sf::Vector2f target, const std::vector<sf::Vector2f>& possibleDirs, const std::vector<std::string>& map);
};
