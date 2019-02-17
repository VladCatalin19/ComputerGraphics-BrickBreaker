#pragma once

#include "Level.h"

class Level3 : public Level {
public:
    Level3();
    Level3(glm::ivec2 resolution);
    ~Level3();

    void InitLevelDependentConstants() override;
    Brick::BrickType CalculateBrickType(int x, int y) override;
};