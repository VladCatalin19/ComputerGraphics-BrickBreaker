#pragma once

#include "Level.h"

class Level2 : public Level {
public:
    Level2();
    Level2(glm::ivec2 resolution);
    ~Level2();

    void InitLevelDependentConstants() override;
    Brick::BrickType CalculateBrickType(int x, int y) override;
};