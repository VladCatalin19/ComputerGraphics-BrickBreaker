#include "Level.h"

#include <iostream>
using namespace std;

Level::Level() {
    platform = NULL;

    for (int i = 0; i < WALLS_NUMBER; ++i) {
        walls[i] = NULL;
    }

    ball = NULL;

    bricksRows = 0;
    bricksColumns = 0;
    bricks = NULL;

    for (int i = 0; i < POWERUPS_NUMBER; ++i) {
        powerUps[i] = NULL;
    }

    lives = NULL;
}

Level::~Level() {
    delete platform;

    for (int i = 0; i < 3; ++i) {
        delete walls[i];
    }

    delete ball;

    for (int i = 0; i < bricksRows; ++i) {
        for (int j = 0; j < bricksColumns; ++j) {
            delete bricks[i][j];
        }
        delete bricks[i];
    }

    delete bricks;

    for (int i = 0; i < POWERUPS_NUMBER; ++i) {
        delete powerUps[i];
    }

    delete lives;
}

Level::Level(glm::ivec2 resolution) {
    this->resolution = resolution;
}

void Level::InitLevel() {
    InitLevelDependentConstants();
    InitConstants();
    InitPlatform();
    InitWalls();
    InitBall();
    InitBricks();
    InitLives();
    InitPowerUps();
}


void Level::InitLevelDependentConstants() {

}

void Level::InitConstants() {
    // Platform
    platformWidth = 200.0f;
    platformHeight = 10.0f;
    platformColor = glm::vec3(0.0f, 1.0f, 0.0f);
    failZoneHeight = platformHeight * 2.0f;

    // Walls
    wallsThickness = 25.0f;
    wallsColor = glm::vec3(1.0f, 0.0f, 0.0f);

    // Ball
    ballRadius = 10.0f;
    ballStartHeight = failZoneHeight + platformHeight + ballRadius * 4.0f;
    ballColor = glm::vec3(1.0f, 1.0f, 1.0f);

    // Bricks
    remainingBricks = bricksRows * bricksColumns;
    brickColors[0] = glm::vec3(1.0f, 0.0f, 1.0f);
    brickColors[1] = glm::vec3(0.7f, 0.0f, 0.7f);
    brickColors[2] = glm::vec3(0.4f, 0.0f, 0.4f);
    brickColors[3] = glm::vec3(0.4f, 0.4f, 1.0f);

    // Lives
    spaceBetweenLives = 2.0f * ballRadius + 10.0f;

    // PowerUps
    squareLength = 15.0f;
    powerUpsColors[0] = ballColor;
    powerUpsColors[1] = platformColor;
    powerUpsColors[2] = glm::vec3(1.0f, 0.5f, 0.0f);
}

void Level::InitPlatform() {
    float x = ((float)(resolution.x) - platformWidth) / 2.0f;
    glm::vec3 platformPosition = glm::vec3(x, failZoneHeight, 0);

    platform = new Platform(platformPosition, platformColor,
                            platformWidth, platformHeight);
}

void Level::InitWalls() {
    walls[0] = new Wall(glm::vec3(0.0f, 0.0f, 0.0f),
                       wallsColor,
                       wallsThickness,
                       (float)(resolution.y) - 0.0f);
    walls[1] = new Wall(glm::vec3(0.0f,
                                  (float)(resolution.y) - wallsThickness,
                                  0.0f),
                       wallsColor,
                       (float)(resolution.x),
                       wallsThickness);
    walls[2] = new Wall(glm::vec3((float)(resolution.x) - wallsThickness,
                                  0.0f,
                                  0.0f),
                       wallsColor,
                       wallsThickness,
                       (float)(resolution.y));
}

void Level::InitBall() {
    glm::vec3 ballPosition = glm::vec3((float)(resolution.x) / 2.0f,
                                       ballStartHeight, 0.0f);
    ball = new Ball(ballPosition, ballColor, ballRadius, ballSpeed);
}

void Level::InitBricks() {
    bricks = new Brick**[bricksRows];
    for (int i = 0; i < bricksRows; ++i) {
        bricks[i] = new Brick*[bricksColumns];
    }

    for (int i = 0; i < bricksRows; ++i) {
        float y = firstBrickPos.y + i * (brickHeight + heightBetweenBricks);

        for (int j = 0; j < bricksColumns; ++j) {
            float x = firstBrickPos.x + j * (brickWidth + widthBetweenBricks);
            glm::vec3 pos = glm::vec3(x, y, 0.0f);
            glm::vec3 color = brickColors[0];

            Brick::BrickType brickType = CalculateBrickType(i, j);
            bricks[i][j] = new Brick(pos, color, brickWidth, brickHeight, brickType);
        }
    }
}

void Level::InitLives() {
    glm::vec3 livesPosition = glm::vec3(ballRadius + wallsThickness,
                                        failZoneHeight,
                                        0.0f);
    lives = new Lives(livesPosition, initialLives, spaceBetweenLives);
}

Brick::BrickType Level::CalculateBrickType(int x, int y) {
    return Brick::normal;
}

void Level::InitPowerUps() {
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
    srand((unsigned int)time(NULL));

    for (int i = 0; i < POWERUPS_NUMBER; ++i) {
        powerUps[i] = new PowerUp(position,
                                  powerUpsColors[i],
                                  squareLength,
                                  (PowerUp::PowerUpTypes)(i),
                                  powerUpsDurations[i],
                                  powerUpsFallingSpeed);
    }
}

// Base algorithm taken from https://stackoverflow.com/a/402010
glm::vec3 Level::CircleRectIntersect(BrickBreakerObjects::Ball *circle,
                                     BrickBreakerObjects::Rectangle *rect) {

    glm::vec3 rectCenter = glm::vec3(rect->GetPosition().x + rect->GetWidth() / 2.0f,
                                     rect->GetPosition().y + rect->GetHeight() / 2.0f,
                                     0.0f);
    glm::vec3 circleDistance = glm::vec3(abs(circle->GetPosition().x - rectCenter.x),
                                         abs(circle->GetPosition().y - rectCenter.y),
                                         0.0f);

    // Distance on x coordinats is too big
    if (circleDistance.x > (rect->GetWidth() / 2.0f + circle->GetRadius())) {
        return glm::vec3(0.0f, 0.0f, 0.0f);
    }

    // Distance on y coordinats is too big
    if (circleDistance.y > (rect->GetHeight() / 2.0f + circle->GetRadius())) {
        return glm::vec3(0.0f, 0.0f, 0.0f);
    }

    // Circle's center is above or below the rectangle's center and the two
    // objects intersect
    if (circleDistance.x <= (rect->GetWidth() / 2.0f)) {
        return glm::vec3(1.0f, -1.0f, 1.0f);
    }

    // Circle's center is to the left or to the right the rectangle's center
    // and the two objects intersect
    if (circleDistance.y <= (rect->GetHeight() / 2.0f)) {
        return glm::vec3(-1.0f, 1.0f, 1.0f);
    }

    float cornerDistanceX = circleDistance.x - rect->GetWidth() / 2.0f;
    float cornerDistanceY = circleDistance.y - rect->GetHeight() / 2.0f;
    float cornerDistanceSquared = cornerDistanceX * cornerDistanceX
                                + cornerDistanceY * cornerDistanceY;
    // The distance from the circle's center and the closest corner of the
    // rectangle is not bigger than the circle's radius and the two objects
    // do not collide
    if (!(cornerDistanceSquared <= (circle->GetRadius() * circle->GetRadius())) ) {
        return glm::vec3(0.0f, 0.0f, 0.0f);
    }

    // The circle collides with a rectangle's corner
    // Algorithm taken from https://gamedev.stackexchange.com/a/10917 to calculate
    // the direction after reflexion
    float x = circle->GetPosition().x - rectCenter.x - rect->GetWidth() / 2.0f;
    float y = circle->GetPosition().y - rectCenter.y - rect->GetHeight() / 2.0f;
    float c = -2.0f * (circle->GetDirection().x * x + circle->GetDirection().y * y)
              / (x * x + y * y);
    return glm::vec3(circle->GetDirection().x + c * x,
                     circle->GetDirection().y + c * y,
                     0.0f);
}

void Level::ChangeBallPositionAfterCollisionWall(int wallIndex) {
    if (wallIndex == -1) {
        return;
    }

    float xCoord;
    float yCoord;

    switch (wallIndex) {

    case 0: {
        xCoord = walls[wallIndex]->GetPosition().x
               + walls[wallIndex]->GetWidth() + ball->GetRadius();
        yCoord = ball->GetPosition().y;
        break;
    }

    case 1:
        xCoord = ball->GetPosition().x;
        yCoord = walls[wallIndex]->GetPosition().y - ball->GetRadius();
        break;

    case 2:
        xCoord = walls[wallIndex]->GetPosition().x - ball->GetRadius();
        yCoord = ball->GetPosition().y;
        break;
    }
    ball->SetPosition(glm::vec3(xCoord, yCoord, 0.0f));
}

void Level::ChangeBallDirectionAfterCollision(glm::vec3 direction) {
    if (direction != glm::vec3(0.0f, 0.0f, 0.0f)) {
        glm::vec3 newDirection;
        if (direction == glm::vec3(1.0f, -1.0f, 1.0f) ||
            direction == glm::vec3(-1.0f, 1.0f, 1.0f)) {
            newDirection = ball->GetDirection() * direction;
        } else {
            newDirection = direction;
        }
        ball->SetDirection(newDirection);
    }
}

void Level::CheckWallColisionAndUpdateBall() {
    glm::vec3 direction;

    // Check collision with all walls and, if collision found, apply reflexion
    for (int i = 0; i < WALLS_NUMBER; ++i) {
        direction = CircleRectIntersect(ball, walls[i]);

        // If collision found, skip the rest of the walls
        if (direction != glm::vec3(0.0f, 0.0f, 0.0f)) {
            ChangeBallPositionAfterCollisionWall(i);
            ChangeBallDirectionAfterCollision(direction);
            break;
        }
    }
}

void Level::CheckPlatformCollisionAndUpdateBall() {
    glm::vec3 direction = CircleRectIntersect(ball, platform);
    if (direction != glm::vec3(1.0f, -1.0f, 1.0f)) {
        return;
    }

    float platformCenterX = platform->GetPosition().x + platform->GetWidth() / 2.0f;

    // x is cosine
    float x = ((ball->GetPosition().x - platformCenterX) / platform->GetWidth()) * 2.0f;
    // y is sine
    float y = sqrt(1.0f - x * x);

    ball->SetDirection(glm::vec3(x, y, 0.0f));
}

void Level::CheckBrickCollisionAndUpdateBall() {
    float firstBrickX = firstBrickPos.x;
    float firstBrickY = firstBrickPos.y;

    // If ball is to the left of the brick matrix, it will not collide with
    // any bricks
    if (ball->GetPosition().x + ball->GetRadius() < firstBrickX) {
        return;
    }

    // If ball is below the brick matrix, it will not collide with any bricks
    if (ball->GetPosition().y + ball->GetRadius() < firstBrickY) {
        return;
    }

    float lastBrickX = firstBrickX + (brickWidth + widthBetweenBricks)
                                   * bricksColumns;
    float lastBrickY = firstBrickY + (brickHeight + heightBetweenBricks)
                                   * bricksRows;

    // If ball is to the right of the brick matrix, it will not collide with
    // any bricks
    if (ball->GetPosition().x - ball->GetRadius() > lastBrickX + brickWidth) {
        return;
    }

    // If ball is above the brick matrix, it will not collide with any bricks
    if (ball->GetPosition().y - ball->GetRadius() > lastBrickY + brickHeight) {
        return;
    }
    
    // If the ball is near or inside the matrix, the ball's x coordinate will be
    // between 2 bricks x coordinates and the y coordninate will be between 2
    // bricks y coordinates
    // Calculate the x coordinates of the enclosing bricks
    int auxX[2];
    auxX[0] = (int)((ball->GetPosition().x - firstBrickX)
                    / (brickWidth + widthBetweenBricks));
    auxX[1] = auxX[0] + 1;

    // Calculate the y coordinates of the enclosing bricks
    int auxY[2];
    auxY[0] = (int)((ball->GetPosition().y - firstBrickY)
                    / (brickHeight + heightBetweenBricks));
    auxY[1] = auxY[0] + 1;
    
    // Create a queue that will contain the bricks
    #define QUEUE_SIZE 4
    Brick *queue[QUEUE_SIZE];
    for (int i = 0; i < QUEUE_SIZE; ++i) {
        queue[i] = NULL;
    }

    // Add the bricks to the queue if their indices exist and if the bricks are
    // not destroyed
    for (int i = 0; i < 2; ++i) {

        // Check if y indices exist
        if (auxY[i] >= 0 && auxY[i] < bricksRows) {
            for (int j = 0; j < 2; ++j) {

                // Check if x indices exist and brick is not destroyed
                if ((auxX[j] >= 0 && auxX[j] < bricksColumns)
                    && bricks[auxY[i]][auxX[j]]->GetDestroyStatus()
                        == Brick::notDestroyed) {

                    queue[i * 2 + j] = bricks[auxY[i]][auxX[j]];
                }
            }
        }
    }

    // Check collsiion between the ball and the bricks from the queue
    bool foundCollision = false;
    for (int i = 0; i < QUEUE_SIZE && !foundCollision; ++i) {
        if (queue[i] == NULL) {
            continue;
        }

        // Skip if no collision detected
        glm::vec3 direction = CircleRectIntersect(ball, queue[i]);
        if (direction == glm::vec3(0.0f, 0.0f, 0.0f)) {
            continue;
        }

        // Change ball's direction only if 'no reflexion' powerup is not active
        if (!(powerUps[POWERUPS_NO_RELFLEXION]->IsActive())) {
            ChangeBallDirectionAfterCollision(direction);
        }

        // Damage the brick and destroy if health reacheas 0
        queue[i]->Damage(remainingBricks);
        if (queue[i]->GetDestroyStatus() != Brick::notDestroyed) {
            --remainingBricks;
        }

        // If brick was destroyed, add it to the list of destroying bricks to
        // play its animation
        if (queue[i]->GetDestroyStatus() == Brick::destroying) {
            destroyingBricks.push_back(queue[i]);

            // Generate powerup if lucky
            int probability = rand() % 100;
            if (probability < powerUpsProbabilityToSpawn) {
                PowerUp::PowerUpTypes type;
                int biggerBallProb = powerUpsTypeProbability[POWERUPS_BIGGER_BALL];
                int biggerPlatfProb = powerUpsTypeProbability[POWERUPS_BIGGER_BALL]
                    + powerUpsTypeProbability[POWERUPS_BIGGER_PLATFORM];

                probability = rand() % 100;
                if (probability < biggerBallProb) {
                    type = PowerUp::biggerBall;

                } else if (probability >= biggerBallProb
                           && probability < biggerPlatfProb) {
                    type = PowerUp::biggerPlatform;

                } else {
                    type = PowerUp::noReflexion;
                }

                // Spawn powerup from brick's center
                float x = queue[i]->GetPosition().x + queue[i]->GetWidth() / 2.0f;
                float y = queue[i]->GetPosition().y + queue[i]->GetHeight() / 2.0f;

                PowerUp *powerUp = new PowerUp(glm::vec3(x, y, 0.0f),
                                               powerUpsColors[(int)(type)],
                                               squareLength, type,
                                               powerUpsDurations[(int)(type)],
                                               powerUpsFallingSpeed);
                fallingPowerUps.push_back(powerUp);
            }
        }

        foundCollision = true;
    }
}

void Level::CheckPowerUpColisionAndApplyPowerUp() {
    std::list<PowerUp*>::iterator it = fallingPowerUps.begin();
    while (it != fallingPowerUps.end()) {
        float x = (*it)->GetPosition().x;
        float y = (*it)->GetPosition().y;

        if (y <= platform->GetPosition().y + failZoneHeight
            && (platform->GetPosition().x <= x
                && x <= platform->GetPosition().x + platform->GetWidth())) {

            // Activate powerup since it touched the platofrm
            powerUps[(int)((*it)->GetType())]->Activate();
            delete (*it);
            it = fallingPowerUps.erase(it);

        } else if (y <= 0) {
            
            // Delete the powerup since it did not touch the platform
            delete (*it);
            it = fallingPowerUps.erase(it);
        } else {
            ++it;
        }
    }
}

bool Level::LifeLost() {
    float x = ball->GetPosition().x;
    float y = ball->GetPosition().y;

    if (x < 0.0f || x > resolution.x + ball->GetRadius()) {
        return true;
    }

    if (y < failZoneHeight || y > resolution.y) {
        return true;
    }

    return false;
}

void Level::UpdateDestroyingBricks(float deltaTimeSeconds) {
    if (destroyingBricks.empty()) {
        return;
    }

    // Delete destroyed bricks
    std::list<Brick*>::iterator it = destroyingBricks.begin();
    while (it != destroyingBricks.end()) {
        (*it)->DecreaseDestroyingTimeRemaining(deltaTimeSeconds);

        if ((*it)->GetDestroyingTimeRemaining() <= 0.0f) {
            (*it)->SetDestroyStatus(Brick::destroyed);
            it = destroyingBricks.erase(it);
        } else {
            ++it;
        }
    }
}

void Level::UpdateFallingPowerUps(float deltaTimeSeconds) {
    if (fallingPowerUps.empty()) {
        return;
    }

    for (PowerUp *p : fallingPowerUps) {
        float x = p->GetPosition().x;
        float y = p->GetPosition().y - deltaTimeSeconds * p->GetFallingSpeed();
        p->SetPosition(glm::vec3(x, y, 0.0f));
    }
}

void Level::UpdatePowerUps(float deltaTimeSeconds) {
    for (int i = 0; i < POWERUPS_NUMBER; ++i) {
        // Apply powerups' effects
        if (!powerUps[i]->GetIfEffectIsApplied()
            && powerUps[i]->GetDuration() == powerUps[i]->GetDurationRemaining()) {

            switch (i) {
            case POWERUPS_BIGGER_BALL:
                ball->SetRadius(ball->GetRadius() * ballIncreasingSize);
                powerUps[i]->ApplyEffect();
                break;

            case POWERUPS_BIGGER_PLATFORM: {
                float x = platform->GetPosition().x
                    - (platformIncreasingSize - 1.0f) / 2.0f * platform->GetWidth();
                float y = platform->GetPosition().y;
                glm::vec3 newPos = glm::vec3(x, y, 0.0f);

                platform->SetWidth(platform->GetWidth() * platformIncreasingSize);
                platform->SetPosition(newPos, wallsThickness, (float)(resolution.x));
                powerUps[i]->ApplyEffect();
                break;
            }

            case POWERUPS_NO_RELFLEXION:
                powerUps[i]->ApplyEffect();
                break;
            }

        }

        // Deactivate powerups
        if (powerUps[i]->IsActive() && powerUps[i]->GetDurationRemaining() <= 0.0f) {
            switch (i) {
            case POWERUPS_BIGGER_BALL:
                ball->SetRadius(ball->GetRadius() / ballIncreasingSize);
                powerUps[i]->Deactivate();
                break;

            case POWERUPS_BIGGER_PLATFORM: {
                platform->SetWidth(platform->GetWidth() / platformIncreasingSize);

                float x = platform->GetPosition().x
                    + (platformIncreasingSize - 1.0f) / 2.0f * platform->GetWidth();
                float y = platform->GetPosition().y;
                glm::vec3 newPos = glm::vec3(x, y, 0.0f);

                platform->SetPosition(newPos, wallsThickness, (float)(resolution.x));
                powerUps[i]->Deactivate();
                break;
            }

            case POWERUPS_NO_RELFLEXION:
                powerUps[i]->Deactivate();
                break;
            }
        }

        if (powerUps[i]->IsActive()) {
            powerUps[i]->DecreaseDurationRemaining(deltaTimeSeconds);
        }
    }
}

void Level::Update(float deltaTimeSeconds) {
    UpdateDestroyingBricks(deltaTimeSeconds);
    UpdateFallingPowerUps(deltaTimeSeconds);
    UpdatePowerUps(deltaTimeSeconds);

    CheckWallColisionAndUpdateBall();
    CheckPlatformCollisionAndUpdateBall();
    CheckBrickCollisionAndUpdateBall();
    CheckPowerUpColisionAndApplyPowerUp();

    // Move ball
    if (ball->IsLaunched()) {
        // Update coordinates
        float x = ball->GetPosition().x + ball->GetDirection().x
                                        * ball->GetSpeed() * deltaTimeSeconds;
        float y = ball->GetPosition().y + ball->GetDirection().y
                                        * ball->GetSpeed() * deltaTimeSeconds;
        ball->SetPosition(glm::vec3(x, y, 0.0f));
    }

    if (LifeLost()) {
        lives->LoseOneLife();
        float platformCenterX = platform->GetPosition().x
                              + platform->GetWidth() / 2.0f;
        ball->Reset(glm::vec3(platformCenterX, ballStartHeight, 0.0f));
    }
}

bool Level::HasWon() {
    return remainingBricks == 0;
}

bool Level::HasLost() {
    return lives->IsDead();
}

// Getters

Platform* Level::GetPlatform() {
    return platform;
}

Wall** Level::GetWalls() {
    return walls;
}

Ball* Level::GetBall() {
    return ball;
}

int Level::GetBricksRows() {
    return bricksRows;
}

int Level::GetBricksColumns() {
    return bricksColumns;
}

Brick*** Level::GetBricks() {
    return bricks;
}

glm::vec3* Level::GetBrickColors() {
    return brickColors;
}

PowerUp** Level::GetPowerUps() {
    return powerUps;
}

std::list<BrickBreakerObjects::PowerUp*> Level::GetFallingPowerUp() {
    return fallingPowerUps;
}

float Level::GetBallIncreasingSize() {
    return ballIncreasingSize;
}
float Level::GetPlatformIncreasingSize() {
    return platformIncreasingSize;
}

Lives* Level::GetLives() {
    return lives;
}

int Level::GetLevelNumber() {
    return levelNumber;
}
