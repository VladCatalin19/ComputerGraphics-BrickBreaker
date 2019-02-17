#pragma once

#include "Rectangle.h"

/**
 * This class implements the immovable walls in the scene. The ball will collide
 * with the walls and will be reflected in the other direction it came from.
 */
class BrickBreakerObjects::Wall : public BrickBreakerObjects::Rectangle {
public:
    Wall();
    Wall(glm::vec3 position, glm::vec3 color, float width, float height);
    ~Wall();
};