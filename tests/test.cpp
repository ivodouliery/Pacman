// Indique à Catch2 de fournir une fonction main() ici
// (Attention : il ne faut qu'un seul main() par projet actif)
#define CATCH_CONFIG_MAIN 

#include "../vendor/catch_amalgamated.hpp"

// Un test simple pour vérifier que le framework fonctionne
TEST_CASE("Verification de l'installation de Catch2", "[vendor]") {
    REQUIRE(1 + 1 == 2);
    REQUIRE(true == true);
}

// Un test pour vérifier que vos includes fonctionnent aussi
#include "../include/Map.hpp"

TEST_CASE("Verification des constantes Map", "[map]") {
    // Vérifie simplement qu'on peut accéder aux constantes de Map
    REQUIRE(Map::cellSize == 16.0f);
    REQUIRE(Map::MAP_WIDTH == 28);
}