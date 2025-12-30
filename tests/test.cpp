#include <catch2/catch_test_macros.hpp>
#include "../include/Map.hpp"

TEST_CASE("Map dimensions are correct", "[map]") {
    REQUIRE(Map::MAP_WIDTH == 28);
    REQUIRE(Map::MAP_HEIGHT == 30);
    REQUIRE(Map::cellSize == 16.0f);
}