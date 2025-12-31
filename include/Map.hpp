#pragma once
#include <SFML/Graphics.hpp>
#include "Ghost.hpp"
#include "Pacman.hpp"
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
     * @brief Met à jour la carte.
     * 
     * Met à jour la position des entités sur la carte.
     */
    void update();

    /**
     * @brief Gère les entrées du joueur.
     * @param key La touche appuyée.
     */
    void handleInput(sf::Keyboard::Key key);

    /**
     * @brief Démarre le jeu.
     */
    void start();


private:
    /**
     * @brief Indique si le jeu a commencé.
     */
    bool started = false;
    /**
     * @brief La carte du jeu.
     */
    std::vector<std::string> mapGrid;
    /**
     * @brief La texture de la carte.
     */
    sf::Texture mapTexture;
    /**
     * @brief La texture de la carte de début.
     */
    sf::Texture mapStartTexture;
    /**
     * @brief Le sprite de la carte.
     */
    sf::Sprite mapSprite;
    /**
     * @brief La texture des points.
     */
    sf::Texture itemTexture;
    /**
     * @brief Le sprite des points.
     */
    sf::Sprite dotSprite;
    /**
     * @brief Le sprite des super points.
     */
    sf::Sprite superDotSprite;

    /**
     * @brief Pac-Man.
     */
    Pacman pacman;
    /**
     * @brief Blinky.
     */
    Ghost blinky;
    /**
     * @brief Pinky.
     */
    Ghost pinky;
    /**
     * @brief Inky.
     */
    Ghost inky;
    /**
     * @brief Clyde.
     */
    Ghost clyde;
    
};
