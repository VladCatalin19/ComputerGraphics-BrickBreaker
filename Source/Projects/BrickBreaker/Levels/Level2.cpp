#include "Level2.h"

Level2::Level2() : Level() {
    
}

Level2::Level2(glm::ivec2 resolution) : Level(resolution) {

}

Level2::~Level2() {

}

void Level2::InitLevelDependentConstants() {
    // Ball
    ballSpeed = 500.0f;

    // Bricks
    brickWidth = 40.0f;
    brickHeight = 20.0f;
    widthBetweenBricks = 1.75f * brickWidth;
    heightBetweenBricks = 1.75f *brickHeight;
    bricksRows = 7;
    bricksColumns = 10;
    float firstLineY = resolution.y * 0.4f;
    float firstColumnX = (resolution.x - (bricksColumns * brickWidth
                                       + (bricksColumns - 1)
                                       * widthBetweenBricks)) / 2.0f;
    firstBrickPos = glm::vec3(firstColumnX, firstLineY, 0.0);

    // PowerUps
    powerUpsDurations[0] = 10.0f;
    powerUpsDurations[1] = 10.0f;
    powerUpsDurations[2] = 3.0f;
    powerUpsProbabilityToSpawn = 15;
    powerUpsTypeProbability[0] = 40;
    powerUpsTypeProbability[1] = 40;
    powerUpsTypeProbability[2] = 20;

    powerUpsFallingSpeed = 150.0f;
    ballIncreasingSize = 2.0f;
    platformIncreasingSize = 1.5f;

    // Lives
    initialLives = 4;

    // Level number
    levelNumber = 2;
}

Brick::BrickType Level2::CalculateBrickType(int x, int y) {
    if (x % 2 == 0) {
        if (y == 1 || y == 8) {
            return Brick::doubleHP;
        } 
        
        if (y == 3 || y == 6) {
            return Brick::tripleHP;
        }

        return Brick::normal;
    }

    if (y == 2 || y == 7) {
        return Brick::doubleHP;
    }

    if (y == 4 || y == 5) {
        return Brick::tripleHP;
    }

    return Brick::normal;
}