#pragma once
#include "Entity.hpp"

/**
 * @file Pacman.hpp
 * @brief Définition de la classe Pacman contrôlée par le joueur.
 * 
 * Ce fichier contient la classe Pacman qui hérite de Entity.
 * Elle gère les spécificités du personnage principal : vies, mouvement spécifique, animation.
 */

/**
 * @class Pacman
 * @brief Classe représentant le personnage du joueur.
 * 
 * Pacman est une entité qui se déplace sur la grille, mange des pac-gommes
 * et possède un nombre limité de vies.
 */
class Pacman : public Entity {
public:
    /**
     * @brief Constructeur de Pacman.
     * 
     * Initialise la texture, la vitesse et les paramètres d'animation de Pacman.
     */
    Pacman();

    /**
     * @brief Dessine Pacman sur la fenêtre.
     * 
     * @param window La fenêtre de rendu SFML.
     */
    void draw(sf::RenderWindow& window) override;

    /**
     * @brief Met à jour l'état de Pacman.
     * 
     * Gère le mouvement, l'animation (bouche qui s'ouvre/ferme) et la rotation du sprite
     * en fonction de la direction.
     * 
     * @param dt Temps écoulé depuis la dernière frame.
     * @param map La grille du niveau.
     */
    void update(float dt, const std::vector<std::string>& map) override;

    /**
     * @brief Définit la position de Pacman.
     * 
     * @param x Coordonnée X.
     * @param y Coordonnée Y.
     */
    void setPosition(float x, float y) override;

    /**
     * @brief Vérifie si Pacman peut se déplacer vers une position.
     * 
     * Surcharge la méthode de base pour interdire l'accès à la maison des fantômes (portes '-').
     * 
     * @param map La grille du niveau.
     * @param x Coordonnée X cible.
     * @param y Coordonnée Y cible.
     * @return true si le mouvement est autorisé, false sinon.
     */
    bool canMove(const std::vector<std::string>& map, float x, float y) override;
    
    /**
     * @brief Décrémente le nombre de vies de Pacman.
     */
    void removeLife() { lives--; }

    /**
     * @brief Récupère le nombre de vies restantes.
     * @return Le nombre de vies.
     */
    int getLives() const { return lives; }

    /**
     * @brief Réinitialise le nombre de vies à sa valeur par défaut (2).
     */
    void resetLives() { lives = 2; }
    
private:
    /**
     * @brief Nombre de vies restantes.
     * 
     * Initialisé à 2 (donc 3 vies au total avec la vie courante).
     */
    int lives = 2;
};
