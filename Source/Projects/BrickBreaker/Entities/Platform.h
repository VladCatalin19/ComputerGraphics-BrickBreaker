#pragma once

#include "Rectangle.h"

/**
 * This class implements the movable platform in the scene. The platform will
 * move only on the X axis dictated by the mouse position in the scene. It will
 * not go through walls and will collide with the ball. The ball will be reflec-
 * ted making an acute angle with the center of the platform.
 */
class BrickBreakerObjects::Platform : public BrickBreakerObjects::Rectangle {
public:
    Platform();
    Platform(glm::vec3 position, glm::vec3 color, float width, float height);
    ~Platform();

    void SetPosition(glm::vec3 position);
    // Overloads the original function to make sure the plaform will not go
    // through walls
    void SetPosition(glm::vec3 position, float wallsThickness, float resolutionX);
};