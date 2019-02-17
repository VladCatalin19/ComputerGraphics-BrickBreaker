#include "Ball.h"

using namespace BrickBreakerObjects;

Ball::Ball() {

}

Ball::Ball(glm::vec3 position, glm::vec3 color, float radius, float speed)
        : Circle(position, color, radius) {
    this->speed = speed;
    isLaunched = false;
    direction = glm::vec3(0.0f, 0.0f, 0.0f);
}

Ball::~Ball() {

}

float Ball::GetSpeed() {
    return speed;
}

void Ball::Reset(glm::vec3 position) {
    isLaunched = false;
    SetPosition(position);
}

bool Ball::IsLaunched() {
    return isLaunched;
}

void Ball::Launch() {
    isLaunched = true;
    direction = startingDirection;
}

glm::vec3 Ball::GetDirection() {
    return direction;
}

void Ball::SetDirection(glm::vec3 direction) {
    this->direction = direction;
}