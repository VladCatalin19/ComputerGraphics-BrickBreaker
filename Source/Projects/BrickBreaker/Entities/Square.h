#pragma once

#include "Entity.h"

/**
 * This class implements a square type object to be used in the scene.
 */
class BrickBreakerObjects::Square : public BrickBreakerObjects::Entity {
public:
    Square();
    Square(glm::vec3 position, glm::vec3 color, float length);
    ~Square();

    float GetLength();

private:
    float length;
};