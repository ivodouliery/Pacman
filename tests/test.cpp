#include <catch2/catch_test_macros.hpp>

TEST_CASE("Verification de l'installation de Catch2", "[vendor]") {
    REQUIRE(1 + 1 == 2);
    REQUIRE(true == true);
}
