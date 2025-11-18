#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

enum class GhostType {
    BLINKY,  // Red - the most aggressive, he directly chases Pac-Man
    PINKY,   // Pink - tries to ambush you by aiming ahead of your position.
    INKY,    // Blue - calculates a weird combo of your position + Blinky’s position, making him unpredictable.
    CLYDE    // Orange - alternates between chasing and fleeing, chaotic but fun.
};