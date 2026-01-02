#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include "Ghost.hpp"
#include "Pacman.hpp"
#include <vector>
#include <string>

/**
 * @file Map.hpp
 * @brief Définition de la classe Map gérant le niveau de jeu.
 * 
 * Ce fichier contient la classe Map qui orchestre le jeu : la grille, les entités (Pacman, Fantômes),
 * le score, l'interface utilisateur et la logique de jeu (collisions, états).
 */

/**
 * @class Map
 * @brief Classe principale gérant la logique et l'affichage du niveau.
 * 
 * La classe Map charge la configuration du niveau, gère les interactions entre Pacman,
 * les fantômes et les éléments du décor (pac-gommes, murs). Elle gère également
 * le score et l'affichage global du jeu.
 */
class Map {
public:
    /**
     * @brief Taille d'une case/item (16x16 pixels).
     */
    static constexpr int itemSize = 16;
    
    /**
     * @brief Taille visuelle de Pac-Man (24.0f pixels).
     */
    static constexpr float pacmanSize = 24.0f;

    /**
     * @brief Largeur de la carte en nombre de cases.
     */
    static constexpr int MAP_WIDTH = 28;

    /**
     * @brief Hauteur de la carte en nombre de cases.
     */
    static constexpr int MAP_HEIGHT = 30;

    /**
     * @brief Position X de l'origine de la grille à l'écran.
     */
    static constexpr int gridOriginX = 16;

    /**
     * @brief Position Y de l'origine de la grille à l'écran.
     */
    static constexpr int gridOriginY = 112;

    /**
     * @brief Constructeur par défaut.
     * 
     * Initialise la carte, charge les textures, configure les sprites et place les entités
     * à leurs positions initiales.
     */
    Map();

    /**
     * @brief Dessine l'ensemble du niveau sur la fenêtre.
     * 
     * Affiche la carte, les pac-gommes, les entités (Pacman, Fantômes) et l'interface utilisateur (Score, Vies).
     * 
     * @param window La fenêtre de rendu SFML.
     */
    void draw(sf::RenderWindow& window);

    /**
     * @brief Met à jour la logique du niveau.
     * 
     * Gère les déplacements, les collisions, la collecte des pac-gommes,
     * les modes des fantômes et les conditions de victoire/défaite.
     */
    void update();

    /**
     * @brief Gère les entrées du joueur pour contrôler Pacman.
     * 
     * @param key La touche du clavier appuyée.
     */
    void handleInput(sf::Keyboard::Key key);

    /**
     * @brief Démarre la partie.
     * 
     * Passe l'état du jeu à "démarré" et change l'affichage si nécessaire.
     */
    void start();

    /**
     * @brief Réinitialise les positions des entités (Pacman et Fantômes).
     * 
     * Utilisé après la perte d'une vie ou au début d'un niveau.
     */
    void resetPositions();
    
    /**
     * @brief Réinitialise le niveau complet.
     * 
     * Remet les pac-gommes, réinitialise les positions, mais conserve le score et les vies
     * (sauf en cas de Game Over où tout est reset).
     */
    void resetLevel();

    /**
     * @brief Récupère le score actuel du joueur.
     * @return Le score courant.
     */
    int getScore() const;

    /**
     * @brief Récupère le meilleur score enregistré.
     * @return Le high score.
     */
    int getHighScore() const;


private:
    /**
     * @brief Indique si la partie a commencé (après l'écran titre).
     */
    bool started = false;

    /**
     * @brief Représentation textuelle de la grille du niveau.
     * 
     * Chaque caractère représente un élément (mur, vide, pac-gomme, porte, etc.).
     */
    std::vector<std::string> mapGrid;

    /**
     * @brief Texture de l'arrière-plan du niveau.
     */
    sf::Texture mapTexture;

    /**
     * @brief Texture de l'écran de démarrage.
     */
    sf::Texture mapStartTexture;

    /**
     * @brief Sprite affichant l'arrière-plan du niveau.
     */
    sf::Sprite mapSprite;

    /**
     * @brief Texture contenant les sprites des items (pac-gommes).
     */
    sf::Texture itemTexture;

    /**
     * @brief Sprite pour dessiner une pac-gomme normale.
     */
    sf::Sprite dotSprite;

    /**
     * @brief Sprite pour dessiner une super pac-gomme.
     */
    sf::Sprite superDotSprite;

    /**
     * @brief Instance de Pacman contrôlée par le joueur.
     */
    Pacman pacman;

    /**
     * @brief Fantôme rouge (Blinky).
     */
    Ghost blinky;

    /**
     * @brief Fantôme rose (Pinky).
     */
    Ghost pinky;

    /**
     * @brief Fantôme bleu (Inky).
     */
    Ghost inky;

    /**
     * @brief Fantôme orange (Clyde).
     */
    Ghost clyde;
    
    // UI Elements
    /**
     * @brief Score actuel du joueur.
     */
    int m_score = 0;

    /**
     * @brief Meilleur score de la session.
     */
    int m_highScore = 0;

    /**
     * @brief Police d'écriture pour l'interface.
     */
    sf::Font m_font;

    /**
     * @brief Label "Score".
     */
    sf::Text m_lblScore;

    /**
     * @brief Texte affichant la valeur du score.
     */
    sf::Text m_txtScore;

    /**
     * @brief Label "High Score".
     */
    sf::Text m_lblHighScore;

    /**
     * @brief Texte affichant la valeur du high score.
     */
    sf::Text m_txtHighScore;

    /**
     * @brief Masque pour l'en-tête (non utilisé actuellement).
     */
    sf::RectangleShape m_headerMask;
    
    // Life UI
    /**
     * @brief Sprite utilisé pour afficher les vies restantes (icône Pacman).
     */
    sf::Sprite m_lifeSprite;
    
    // Logic state
    /**
     * @brief Indique si les fantômes sont actifs (sortis de la maison).
     */
    bool m_ghostsActive = false;

    /**
     * @brief Timer pour le mode "Frightened" (fantômes vulnérables).
     */
    float m_frightenedTimer = 0.0f;

    /**
     * @brief Nombre de pac-gommes restantes sur la carte.
     */
    int m_remainingDots = 0;
};
