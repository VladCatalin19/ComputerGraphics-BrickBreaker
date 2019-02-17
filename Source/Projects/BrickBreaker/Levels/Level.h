#pragma once

#include <list>
#include <time.h>

#include <Projects/BrickBreaker/Entities/Entity.h>
#include <Projects/BrickBreaker/Entities/Platform.h>
#include <Projects/BrickBreaker/Entities/Ball.h>
#include <Projects/BrickBreaker/Entities/Wall.h>
#include <Projects/BrickBreaker/Entities/Brick.h>
#include <Projects/BrickBreaker/Entities/Lives.h>
#include <Projects/BrickBreaker/Entities/PowerUp.h>
#include <Projects/BrickBreaker/ShapeCreator/ShapeCreator2D.h>
#include <Projects/BrickBreaker/ShapeCreator/Transform2D.h>

#define BRICKS_TYPE_NUMBER          4
#define POWERUPS_NUMBER             3
#define WALLS_NUMBER                3
#define POWERUPS_BIGGER_BALL        0
#define POWERUPS_BIGGER_PLATFORM    1
#define POWERUPS_NO_RELFLEXION      2

using namespace BrickBreakerObjects;

/**
 * This class implements the logic of a level. A level contains a platform,
 * 3 walls, a ball, a brick matrix, the number of lives the player has in the
 * level and powerup which will drop upon destroying a brick.
 * Initially, the platform and the ball are controlled by the mouse movement on
 * the OX axis. When the user clicks the right button, the ball is sent in the
 * scene. It will collide with the bricks, walls, and platform and will change
 * direction accordingly. When a powerup is spawned, the user can catch it with
 * the platform and activate it.
 * Destroying all bricks will complete the level, losing all lives will result
 * in failing the level.
 */
class Level {
public:
    Level();
    Level(glm::ivec2 resolution);
    ~Level();

protected:
    Platform *platform;
    float platformWidth;
    float platformHeight;
    // If ball's center reaches this height, one life will be lost
    float failZoneHeight;
    glm::vec3 platformColor;

    Wall *walls[WALLS_NUMBER];
    float wallsThickness;
    glm::vec3 wallsColor;

    Ball *ball;
    float ballRadius;
    float ballStartHeight;
    float ballSpeed;
    glm::vec3 ballColor;

    Brick ***bricks;
    float brickWidth;
    float brickHeight;
    // Empty space between bricks
    float widthBetweenBricks;
    float heightBetweenBricks;
    int bricksRows;
    int bricksColumns;
    glm::vec3 brickColors[BRICKS_TYPE_NUMBER];
    // x and y coordinats of the first brick, used to calculate other bricks'
    // coordinates
    glm::vec3 firstBrickPos;
    // Number of bricks which are not destroyed
    int remainingBricks;
    // List with bricks which play they destroying animation
    std::list<BrickBreakerObjects::Brick*> destroyingBricks;

    Lives *lives;
    int initialLives;
    // Empty space between lives' meshes
    float spaceBetweenLives;

    PowerUp *powerUps[POWERUPS_NUMBER];
    float powerUpsDurations[POWERUPS_NUMBER];
    int powerUpsProbabilityToSpawn;
    int powerUpsTypeProbability[POWERUPS_NUMBER];
    std::list<BrickBreakerObjects::PowerUp*> fallingPowerUps;
    // Length of a powerup mesh
    float squareLength;
    float powerUpsFallingSpeed;
    glm::vec3 powerUpsColors[POWERUPS_NUMBER];

    // Percentage the ball will increase in size
    float ballIncreasingSize;
    // Percentage the platform will increase in size
    float platformIncreasingSize;
 
    int levelNumber;
    glm::ivec2 resolution;

    // Each level will override the constants in order to create diversity
    void virtual InitLevelDependentConstants();

    void InitConstants();
    void InitPlatform();
    void InitWalls();
    void InitBall();
    void InitBricks();
    void InitPowerUps();
    void InitLives();

    // Each level will have a unique brick matrix, the function will calculate
    // the type of a brick in the matrix
    Brick::BrickType virtual CalculateBrickType(int x, int y);

    // Checks if a circle intersects a rectangle
    glm::vec3 CircleRectIntersect(BrickBreakerObjects::Ball *circle,
                                  BrickBreakerObjects::Rectangle *rect);
    void ChangeBallDirectionAfterCollision(glm::vec3 direction);
    void CheckWallColisionAndUpdateBall();
    void CheckPlatformCollisionAndUpdateBall();
    void CheckBrickCollisionAndUpdateBall();
    void CheckPowerUpColisionAndApplyPowerUp();

    bool LifeLost();

    void UpdateDestroyingBricks(float deltaTimeSeconds);
    void UpdateFallingPowerUps(float deltaTimeSeconds);
    void UpdatePowerUps(float deltaTimeSeconds);

public:
    void InitLevel();
    void Update(float deltaTimeSeconds);

    Platform* GetPlatform();
    Wall** GetWalls();
    Ball* GetBall();
    int GetBricksRows();
    int GetBricksColumns();
    Brick*** GetBricks();
    glm::vec3* GetBrickColors();
    PowerUp** GetPowerUps();
    std::list<BrickBreakerObjects::PowerUp*> GetFallingPowerUp();
    float GetBallIncreasingSize();
    float GetPlatformIncreasingSize();
    Lives* GetLives();
    int GetLevelNumber();
    bool HasLost();
    bool HasWon();
};