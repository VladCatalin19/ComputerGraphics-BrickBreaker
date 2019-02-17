#pragma once

#include "Entity.h"

/**
 * This class implements a circle type object to be used in the scene.
 */
class BrickBreakerObjects::Circle : public BrickBreakerObjects::Entity {
public:
    Circle();
    Circle(glm::vec3 position, glm::vec3 color, float radius);
    ~Circle();

private:
    float radius;

public:
    float GetRadius();
    void SetRadius(float radius);
};