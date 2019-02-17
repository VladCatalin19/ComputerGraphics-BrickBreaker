#pragma once

#include "Rectangle.h"

/**
 * This class implements the immovable bricks in the scene. The brick will be
 * damaged by the ball and will be destroyed when its health reaches 0. When
 * destroyed, the brick will be marked as destroyed and will not interract with
 * the ball anymore.
 */
class BrickBreakerObjects::Brick : public BrickBreakerObjects::Rectangle {
public:
    // Types of bricks a scene can contain
    //      normal - 1 hit to destroy
    //      doubleHP - 2 hits to destroy
    //      tripleHP - 3 hits to destroy
    //      lastToDestroy - can be destroyed only if there are no other bricks
    //                      in the scene
    enum BrickType {normal, doubleHP, tripleHP, lastToDestroy};
    // Status of whether the brick will be ignored by the ball
    enum DestroyStatus {notDestroyed, destroying, destroyed};
    Brick();
    Brick(glm::vec3 position, glm::vec3 color, float width, float height,
          BrickType type = normal);
    ~Brick();


private:
    // Number of hits it takes to destroy the brick, -1 if brick must be
    // destroyed last
    int health;
    BrickType type;
    // When brick is destroyed the variable will count 1 second to play the
    // animation of brick's destroying
    float destroyingTimeRemaining;
    DestroyStatus destroyStatus;

public:
    int GetHealth();
    // Damage the brick and, if there are no more bricks remaining, destroy
    // if last brick to destroy
    void Damage(int remainingBricks);
    BrickType GetType();
    float GetDestroyingTimeRemaining();
    // Decrease the time remaining to play the animation with time seconds
    void DecreaseDestroyingTimeRemaining(float time);
    DestroyStatus GetDestroyStatus();
    void SetDestroyStatus(DestroyStatus destroyStatus);
};