#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

/**
 * @brief Classe représentant la carte du jeu.
 * 
 * La classe Map gère la représentation visuelle de la carte du jeu.
 * Elle charge une carte depuis un fichier texte et la dessine sur la fenêtre.
 */
class Map {
public:
    static constexpr float cellSize = 16.0f; ///< Taille d'une case (16x16 pixels)
    static constexpr int itemSize = 16; ///< Taille d'un point (16x16 pixels)
    static constexpr float pacmanSize = 24.0f; ///< Taille de Pac-Man (16x16 pixels)
    static constexpr int MAP_WIDTH = 28; ///< Largeur de la carte.
    static constexpr int MAP_HEIGHT = 30; ///< Hauteur de la carte.
    static constexpr int gridOriginX = 16;
    static constexpr int gridOriginY = 112;
    /**
     * @brief Constructeur par défaut.
     * 
     * Charge la carte depuis un fichier texte.
     */
    Map();

    /**
     * @brief Dessine la carte sur la fenêtre.
     * 
     * @param window La fenêtre sur laquelle la carte est dessinée.
     */
    void draw(sf::RenderWindow& window);
    /**
     * @brief Vérifie si une case spécifique est un mur.
     * Utile pour la gestion des collisions.
     * * @param x Index X de la case dans la grille (0 à MAP_WIDTH-1).
     * @param y Index Y de la case dans la grille (0 à MAP_HEIGHT-1).
     * @return true Si la case est un mur ou hors limites.
     * @return false Si la case est libre (vide ou pastille).
     */
    bool isWall(int x, int y) const;

    /**
     * @brief Tente de manger une pastille à une position donnée.
     * Modifie la grille si une pastille est présente.
     * * @param x Index X de la case.
     * @param y Index Y de la case.
     * @return int Le score gagné (0 si vide, 10 pour une pastille, 50 pour une super-pastille).
     */
    int tryEat(int x, int y);

private:
    std::vector<std::string> mapGrid; ///< La carte du jeu.
    
};
