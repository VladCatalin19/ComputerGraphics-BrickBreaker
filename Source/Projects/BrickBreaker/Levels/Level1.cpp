#include "Level1.h"

Level1::Level1() : Level() {

}

Level1::Level1(glm::ivec2 resolution) : Level(resolution) {

}

Level1::~Level1() {

}

void Level1::InitLevelDependentConstants() {
    // Ball
    ballSpeed = 300.0f;

    // Bricks
    brickWidth = 50.0f;
    brickHeight = 25.5f;
    widthBetweenBricks = 0.75f * brickWidth;
    heightBetweenBricks = 0.75f *brickHeight;
    bricksRows = 5;
    bricksColumns = 10;
    float firstLineY = resolution.y * 0.5f;
    float firstColumnX = (resolution.x - (bricksColumns * brickWidth
                                       + (bricksColumns - 1)
                                       * widthBetweenBricks)) / 2.0f;
    firstBrickPos = glm::vec3(firstColumnX, firstLineY, 0.0);

    // PowerUps
    powerUpsDurations[0] = 10.0f;
    powerUpsDurations[1] = 10.0f;
    powerUpsDurations[2] = 5.0f;
    powerUpsProbabilityToSpawn = 25;
    powerUpsTypeProbability[0] = 40;
    powerUpsTypeProbability[1] = 40;
    powerUpsTypeProbability[2] = 20;

    powerUpsFallingSpeed = 100.0f;
    ballIncreasingSize = 2.5f;
    platformIncreasingSize = 2.0f;

    // Lives
    initialLives = 3;

    // Level number
    levelNumber = 1;
}


Brick::BrickType Level1::CalculateBrickType(int x, int y) {
    if (x == 0 || x == bricksRows - 1 || y == 0 || y == bricksColumns - 1) {
        return Brick::doubleHP;
    }

    return Brick::normal;
}