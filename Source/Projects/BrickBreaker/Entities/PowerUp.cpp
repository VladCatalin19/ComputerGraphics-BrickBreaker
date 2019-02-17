#include "PowerUp.h"

using namespace BrickBreakerObjects;

PowerUp::PowerUp() {

}

PowerUp::PowerUp(glm::vec3 position, glm::vec3 color, float length,
    PowerUp::PowerUpTypes type, float duration, float fallingSpeed) 
        : Square(position, color, length) {

    this->type = type;
    active = false;
    effectApplied = false;
    this->duration = duration;
    durationRemaining = 0.0f;
    this->fallingSpeed = fallingSpeed;
}

PowerUp::~PowerUp() {

}

PowerUp::PowerUpTypes PowerUp::GetType() {
    return type;
}

bool PowerUp::IsActive() {
    return active;
}

void PowerUp::Activate() {
    active = true;
    durationRemaining = duration;
}

void PowerUp::Deactivate() {
    active = false;
    effectApplied = false;
    durationRemaining = 0.0f;
}

bool PowerUp::GetIfEffectIsApplied() {
    return effectApplied;
}

void PowerUp::ApplyEffect() {
    effectApplied = true;
}

float PowerUp::GetDuration() {
    return duration;
}

float PowerUp::GetDurationRemaining() {
    return durationRemaining;
}

void PowerUp::DecreaseDurationRemaining(float time) {
    durationRemaining -= time;
}

float PowerUp::GetFallingSpeed() {
    return fallingSpeed;
}