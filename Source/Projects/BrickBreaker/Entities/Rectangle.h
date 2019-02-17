#pragma once

#include "Entity.h"

/**
 * This class implements a rectangle type object to be used in the scene.
 */
class BrickBreakerObjects::Rectangle : public BrickBreakerObjects::Entity {
public:
    Rectangle();
    Rectangle(glm::vec3 position, glm::vec3 color, float width, float height);
    ~Rectangle();

private:
    float width;
    float height;

public:
    float GetWidth();
    void SetWidth(float width);
    float GetHeight();
};