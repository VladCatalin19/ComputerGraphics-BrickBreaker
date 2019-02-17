#pragma once

#include "Level.h"

class Level1 : public Level {
public:
    Level1();
    Level1(glm::ivec2 resolution);
    ~Level1();

    void InitLevelDependentConstants() override;
    Brick::BrickType CalculateBrickType(int x, int y) override;
};