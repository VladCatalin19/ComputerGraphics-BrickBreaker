#pragma once

#include "Square.h"

using namespace BrickBreakerObjects;

/**
 * This class implements the powerups that will fall when destroying a brick.
 * The powerup will start to fall in a direction parallel with OY axis. The
 * powerup will be activated if the platform touches it when it reaches plat-
 * form's height and will be deactivated after a certain amount of time.
 */
class BrickBreakerObjects::PowerUp : public BrickBreakerObjects::Square {
public:
    // Types of powerups destroying a brick can create
    //      biggerBall - increases ball radius
    //      biggerPlatform - increases platform width
    //      noReflexion - ball will not change direction when colliding with
    //                    bricks
    enum PowerUpTypes {biggerBall, biggerPlatform, noReflexion};
    PowerUp();
    PowerUp(glm::vec3 position, glm::vec3 color, float length,
            PowerUpTypes type, float duration, float fallingSpeed);
    ~PowerUp();

private:
    PowerUpTypes type;
    bool active;
    // Used to not apply the same effect more than once
    bool effectApplied;
    // Time the effect will last
    float duration;
    // Time remaining until effect will deactivate
    float durationRemaining;
    // The absolute value of the speed the powerup will fall towards the platform
    float fallingSpeed;

public:
    PowerUpTypes GetType();
    bool IsActive();
    void Activate();
    void Deactivate();
    bool GetIfEffectIsApplied();
    void ApplyEffect();
    float GetDuration();
    float GetDurationRemaining();
    void DecreaseDurationRemaining(float time);
    float GetFallingSpeed();
};