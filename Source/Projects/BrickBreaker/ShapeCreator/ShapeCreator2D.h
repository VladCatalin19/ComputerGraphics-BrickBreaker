#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace ShapeCreator2D {
    // Create rectangle with given bottom left corner, width, height and color
    Mesh* CreateRectangle(std::string name, glm::vec3 leftBottomCorner, float width,
                          float height, glm::vec3 color, bool fill = false);

    // Create square with given bottom left corner, length and color
    Mesh* CreateSquare(std::string name, glm::vec3 leftBottomCorner, float length,
                       glm::vec3 color, bool fill = false);

    // Create circle with given center, radius and color
    Mesh* CreateCircle(std::string name, glm::vec3 center, float radius,
                       glm::vec3 color, bool fill = false);
};