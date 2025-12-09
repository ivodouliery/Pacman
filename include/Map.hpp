/**
 * @file Map.hpp
 * @author Ivo Douliery
 * @brief Fichier de la classe Map.
 * @version 0.1
 * @date 2025-12-09
 * 
 * Ce fichier contient la définition de la classe Map.
 */
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
    /**
     * @brief Taille d'une case (16x16 pixels).
     */
    static constexpr float cellSize = 16.0f;
    /**
     * @brief Taille d'un point (16x16 pixels).
     */
    static constexpr int itemSize = 16;
    /**
     * @brief Taille de Pac-Man (16x16 pixels).
     */
    static constexpr float pacmanSize = 24.0f;
    /**
     * @brief Largeur de la carte.
     */
    static constexpr int MAP_WIDTH = 28;
    /**
     * @brief Hauteur de la carte.
     */
    static constexpr int MAP_HEIGHT = 30;
    /**
     * @brief Position de l'origine de la grille.
     */
    static constexpr int gridOriginX = 16;
    /**
     * @brief Position de l'origine de la grille.
     */
    static constexpr int gridOriginY = 112;
    /**
     * @brief Constructeur par défaut.
     * 
     * C.
     */
    Map(){
        mapGrid = {
            "############################", 
            "#............##............#", 
            "#.####.#####.##.#####.####.#", 
            "#o####.#####.##.#####.####o#", 
            "#..........................#",
            "#.####.##.########.##.####.#", 
            "#.####.##.########.##.####.#",
            "#......##....##....##......#", 
            "######.##### ## #####.######", 
            "     #.##### ## #####.#     ",
            "     #.##    B     ##.#     ",
            "     #.## ###--### ##.#     ",
            "######.## ###--### ##.######",
            "      .   #I P C #   .      ",
            "######.## ######## ##.######",
            "     #.## ######## ##.#     ",
            "     #.##          ##.#     ",
            "     #.##### ## #####.#     ",
            "######.##### ## #####.######", 
            "#............##............#",
            "#.####.#####.##.#####.####.#",
            "#.####.#####.##.#####.####.#",
            "#o..##.......p .......##..o#",
            "###.##.##.########.##.##.###",
            "###.##.##.########.##.##.###",
            "#......##....##....##......#",
            "#.##########.##.##########.#",
            "#.##########.##.##########.#",
            "#..........................#",
            "############################"
        };    
    };

    /**
     * @brief Dessine la carte sur la fenêtre.
     * 
     * @param window La fenêtre sur laquelle la carte est dessinée.
     */
    void draw(sf::RenderWindow& window);

private:
    /**
     * @brief La carte du jeu.
     */
    std::vector<std::string> mapGrid;
    
};
