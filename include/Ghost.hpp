#pragma once
#include "Entity.hpp"
#include <vector>

enum class GhostType {
    BLINKY,  // Red - the most aggressive, he directly chases Pac-Man
    PINKY,   // Pink - tries to ambush you by aiming ahead of your position.
    INKY,    // Blue - calculates a weird combo of your position + Blinky’s position, making him unpredictable.
    CLYDE    // Orange - alternates between chasing and fleeing, chaotic but fun.
};

enum class GhostMode {
    CHASE,      // Chase Pac-Man
    SCATTER,    // Go to corners
    FRIGHTENED, // Vulnérable (super pac-gomme)
    DEAD        // Retourne à la base
};

class Ghost : public Entity {
public:
    Ghost(GhostType type);
    void setPosition(float x, float y) override;

private:
    GhostType type;
    GhostMode mode;
};