#include <catch2/catch_test_macros.hpp>
#include "../include/Map.hpp"
#include "../include/Pacman.hpp"
#include "../include/Ghost.hpp"


TEST_CASE("Map dimensions are correct", "[map]") {
    REQUIRE(Map::MAP_WIDTH == 28);
    REQUIRE(Map::MAP_HEIGHT == 30);
    REQUIRE(Entity::cellSize == 16.0f);
}

TEST_CASE("Pacman movement logic", "[pacman]") {
    Pacman p;

    std::vector<std::string> testMap = {
        "###",
        "#.#",
        "#-#"
    };
    
    float cell = 16.0f;
    float originX = 16.0f;
    float originY = 112.0f;
    
    SECTION("Pacman can move in empty space") {
        float x = originX + 1 * cell;
        float y = originY + 1 * cell;
        REQUIRE(p.canMove(testMap, x, y) == true);
    }

    SECTION("Pacman cannot move into wall") {
        float x = originX + 0 * cell;
        float y = originY + 0 * cell;
        REQUIRE(p.canMove(testMap, x, y) == false);
    }
    
    SECTION("Pacman cannot move into door") {
        float x = originX + 1 * cell;
        float y = originY + 2 * cell;
        REQUIRE(p.canMove(testMap, x, y) == false);
    }
}

TEST_CASE("Pacman lives logic", "[pacman]") {
    Pacman p;
    REQUIRE(p.getLives() == 2);
    
    p.removeLife();
    REQUIRE(p.getLives() == 1);
    
    p.resetLives();
    REQUIRE(p.getLives() == 2);
}

TEST_CASE("Map score logic", "[map]") {
    Map m;
    REQUIRE(m.getScore() == 0);
    REQUIRE(m.getHighScore() == 0);
}

TEST_CASE("Ghost mode and speed logic", "[ghost]") {
    Ghost g(GhostType::BLINKY);

    REQUIRE(g.getMode() == GhostMode::CHASE);
    
    std::vector<std::string> map(30, std::string(28, ' ')); 
    sf::Vector2f pos(0,0);
    
    g.setPosition(32.0f, 128.0f);

    SECTION("Normal speed in CHASE mode") {
        g.setMode(GhostMode::CHASE);
        g.update(0.1f, map, pos);
        REQUIRE(g.getSpeed() == 90.0f);
    }

    SECTION("Slower speed in FRIGHTENED mode") {
        g.setMode(GhostMode::FRIGHTENED);
        g.update(0.1f, map, pos);
        REQUIRE(g.getSpeed() == 50.0f);
    }

    SECTION("Fast speed in DEAD mode") {
        g.setMode(GhostMode::DEAD);
        g.update(0.1f, map, pos);
        REQUIRE(g.getSpeed() == 200.0f);
    }
}

TEST_CASE("Entity direction logic", "[entity]") {
    Pacman p;
    sf::Vector2f dir(1.f, 0.f);
    p.setNextDirection(dir);
    REQUIRE(p.getNextDirection() == dir);
    
    p.setDirection(dir);
    REQUIRE(p.getDirection() == dir);
}

TEST_CASE("Entity position logic", "[entity]") {
    Pacman p;
    p.setPosition(100.f, 200.f);
    REQUIRE(p.getPosition().x == 100.f);
    REQUIRE(p.getPosition().y == 200.f);
}

TEST_CASE("Entity speed logic", "[entity]") {
    Pacman p;
    p.setSpeed(150.f);
    REQUIRE(p.getSpeed() == 150.f);
}

TEST_CASE("Entity alignment logic", "[entity]") {
    Pacman p;
    p.setPosition(21.f, 122.f);

    p.setDirection({0.f, 1.f});
    p.alignToGrid();

    REQUIRE(p.getPosition().x == 16.f);
    
    p.setPosition(21.f, 122.f);

    p.setDirection({1.f, 0.f});
    p.alignToGrid();

    REQUIRE(p.getPosition().y == 128.f);
}

TEST_CASE("Ghost rotation logic", "[ghost]") {
    Ghost g(GhostType::BLINKY);
    g.setRotation(0); // Up
    g.setRotation(1); // Down
    g.setRotation(2); // Left
    g.setRotation(3); // Right
    SUCCEED("Ghost::setRotation executed without crash");
}

TEST_CASE("Map reset logic", "[map]") {
    Map m;
    m.resetLevel();
    REQUIRE(m.getScore() == 0);
    
    m.resetPositions();
    REQUIRE(m.getScore() == 0);
}

