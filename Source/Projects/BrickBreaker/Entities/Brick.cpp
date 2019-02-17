#include "Brick.h"

using namespace BrickBreakerObjects;

Brick::Brick() {

}

Brick::Brick(glm::vec3 position, glm::vec3 color, float width, float height,
        BrickType type) : Rectangle(position, color, width, height){
    switch (type) {
    case normal:
        health = 1;
        break;

    case doubleHP:
        health = 2;
        break;

    case tripleHP:
        health = 3;
        break;

    case lastToDestroy:
        health = -1;
        break;
    }

    this->type = type;
    destroyingTimeRemaining = 0;
    destroyStatus = notDestroyed;
}

Brick::~Brick() {

}

int Brick::GetHealth() {
    return health;
}

void Brick::Damage(int remainingBricks) {
    if (type != lastToDestroy) {
        --health;
    } else if (remainingBricks == 1) {
        health = 0;
    }

    if (health == 0) {
        destroyStatus = destroying;
        destroyingTimeRemaining = 1.0f;
    }
}

Brick::BrickType Brick::GetType() {
    return type;
}

float Brick::GetDestroyingTimeRemaining() {
    return destroyingTimeRemaining;
}

void Brick::DecreaseDestroyingTimeRemaining(float time) {
    destroyingTimeRemaining -= time;
}

Brick::DestroyStatus Brick::GetDestroyStatus() {
    return destroyStatus;
}

void Brick::SetDestroyStatus(Brick::DestroyStatus destroyStatus) {
    this->destroyStatus = destroyStatus;
}