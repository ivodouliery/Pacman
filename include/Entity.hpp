#pragma once
#include <SFML/Graphics.hpp>

class Entity {
public:
    Entity();

    virtual ~Entity() = default;

    virtual void setPosition(float x, float y);
    sf::Vector2f getPosition() const;

    void setSpeed(float speed);
    float getSpeed() const;

    void setDirection(sf::Vector2f direction);
    sf::Vector2f getDirection() const;

    /**
     * @brief Taille d'une entité (32x32 pixels).
     */
    static constexpr int entitySize = 32;

    /**
     * @brief Taille d'une case (16x16 pixels).
     */
    static constexpr float cellSize = 16.0f;

    /**
     * @brief Taille des yeux (16x16 pixels).
     */
    static constexpr int eyesSize = 16;

    virtual void draw(sf::RenderWindow& window) = 0;

    virtual void update(float dt);


protected:
    sf::Vector2f position;
    sf::Vector2f direction;
    float speed;

    sf::Texture texture;
    sf::Sprite sprite_body;
    sf::IntRect textureRect;

};
