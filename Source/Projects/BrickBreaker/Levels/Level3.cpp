#include "Level3.h"

Level3::Level3() : Level() {

}

Level3::Level3(glm::ivec2 resolution) : Level(resolution) {

}

Level3::~Level3() {

}

void Level3::InitLevelDependentConstants() {
    // Ball
    ballSpeed = 700.0f;

    // Bricks
    brickWidth = 40.0f;
    brickHeight = 20.0f;
    widthBetweenBricks = 1.25f * brickWidth;
    heightBetweenBricks = 0.75f *brickHeight;
    bricksRows = 11;
    bricksColumns = 11;
    float firstLineY = resolution.y * 0.3f;
    float firstColumnX = (resolution.x - (bricksColumns * brickWidth
                                       + (bricksColumns - 1)
                                       * widthBetweenBricks)) / 2.0f;
    firstBrickPos = glm::vec3(firstColumnX, firstLineY, 0.0);

    // PowerUps
    powerUpsDurations[0] = 5.0f;
    powerUpsDurations[1] = 5.0f;
    powerUpsDurations[2] = 1.0f;
    powerUpsProbabilityToSpawn = 5;
    powerUpsTypeProbability[0] = 45;
    powerUpsTypeProbability[1] = 50;
    powerUpsTypeProbability[2] = 5;

    powerUpsFallingSpeed = 200.0f;
    ballIncreasingSize = 1.5f;
    platformIncreasingSize = 1.5f;

    // Lives
    initialLives = 5;

    // Level number
    levelNumber = 3;
}


Brick::BrickType Level3::CalculateBrickType(int x, int y) {
    if (x == bricksRows / 2 && y == bricksColumns / 2) {
        return Brick::lastToDestroy;
    }

    if (x == y || x == bricksColumns - y - 1) {
        return Brick::tripleHP;
    }

    if (x == y + 1 || y == x + 1
        || x == bricksColumns - y - 2 || x == bricksRows - y) {
        return Brick::doubleHP;
    }

    return Brick::normal;
}