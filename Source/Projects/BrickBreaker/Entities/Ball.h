#pragma once

#include "Circle.h"

using namespace BrickBreakerObjects;

/**
 * This class implements the ball moving in the scene. It will move evry frame
 * and will collide with te walls, bricks, and platform.
 */
class BrickBreakerObjects::Ball : public BrickBreakerObjects::Circle {
public:
    Ball();
    Ball(glm::vec3 position, glm::vec3 color, float radius, float speed = 0.0f);
    ~Ball();

private:
    // Absolute values of speed vector
    float speed;
    // Checks if ball should move with the platform when mouse movement is
    // detected or move in the scene and collide with other objects
    bool isLaunched;
    // Starting direction of ball when launched, parallel with OY
    const glm::vec3 startingDirection = glm::vec3(0.0f, 1.0f, 0.0f);
    // Direction of ball at current frame 
    glm::vec3 direction;

public:
    float GetSpeed();
    // When life is lost, makes the ball to move with the platform
    void Reset(glm::vec3 position);
    bool IsLaunched();
    // Launch the ball into the scene
    void Launch();
    glm::vec3 GetDirection();
    void SetDirection(glm::vec3 direction);
};