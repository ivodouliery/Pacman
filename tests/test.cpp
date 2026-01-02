#include <catch2/catch_test_macros.hpp>
#include "../include/Map.hpp"
#include "../include/Pacman.hpp"

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
