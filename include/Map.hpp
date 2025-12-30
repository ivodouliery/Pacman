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
    static constexpr float entitySize = 24.0f; ///< Taille des entités (16x16 pixels)
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

private:
    std::vector<std::string> mapGrid; ///< La carte du jeu.
    
};
