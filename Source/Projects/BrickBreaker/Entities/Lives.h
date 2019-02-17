#pragma once

#include "Entity.h"

/**
 * This class implements the lives shown in the bottom-left corner of the scene.
 * When the ball gets out of the screen or if the ball reaches the fail zone, a
 * life is lost.
 */
class BrickBreakerObjects::Lives : public BrickBreakerObjects::Entity {
public:
    Lives();
    Lives(glm::vec3 position, int lives, float spaceBetweenLives);
    ~Lives();

private:
    // Number of lives remaining in a scene
    int lives;
    // Space between lives' meshes
    float spaceBetweenLives;

public:
    int GetLives();
    float GetSpaceBetweenLives();
    // Decrease the number of lives with 1
    void LoseOneLife();
    // Check whether the remaining lives is smaller or equal to 0
    bool IsDead();
};