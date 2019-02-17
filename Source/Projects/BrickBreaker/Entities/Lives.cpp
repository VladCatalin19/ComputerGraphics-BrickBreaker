#include "Lives.h"

using namespace BrickBreakerObjects;

Lives::Lives() {

}

Lives::Lives(glm::vec3 position, int lives, float spaceBetweenLives)
        : Entity(position, glm::vec3()){
    this->lives = lives;
    this->spaceBetweenLives = spaceBetweenLives;
}

Lives::~Lives() {

}

int Lives::GetLives() {
    return lives;
}

float Lives::GetSpaceBetweenLives() {
    return spaceBetweenLives;
}

void Lives::LoseOneLife() {
    --lives;
}

bool Lives::IsDead() {
    return lives <= 0;
}