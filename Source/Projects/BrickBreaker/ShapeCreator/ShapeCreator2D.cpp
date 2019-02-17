#include "ShapeCreator2D.h"

#include <Core/Engine.h>

Mesh* ShapeCreator2D::CreateRectangle(std::string name, glm::vec3 leftBottomCorner,
                                      float width, float height, glm::vec3 color,
                                      bool fill) {
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices = {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(width, 0, 0), color),
        VertexFormat(corner + glm::vec3(width, height, 0), color),
        VertexFormat(corner + glm::vec3(0, height, 0), color)
    };

    Mesh* rectangle = new Mesh(name);
    std::vector<unsigned short> indices = { 0, 1, 2, 3 };

    if (!fill) {
        rectangle->SetDrawMode(GL_LINE_LOOP);
    } else {
        // draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    rectangle->InitFromData(vertices, indices);
    return rectangle;
}

Mesh* ShapeCreator2D::CreateSquare(std::string name, glm::vec3 leftBottomCorner,
                                   float length, glm::vec3 color, bool fill) {
    return ShapeCreator2D::CreateRectangle(name, leftBottomCorner, length,
                                           length, color, fill);
}

Mesh* ShapeCreator2D::CreateCircle(std::string name, glm::vec3 center, float radius,
                                   glm::vec3 color, bool fill) {
    std::vector<VertexFormat> vertices;

    const float PI = 3.1415926f;
    const int fragments = 32;

    float increment = 2.0f * PI / fragments;

    for (float currAngle = 0.0f; currAngle <= 2.0f * PI; currAngle += increment) {
        glm::vec3 point = glm::vec3(radius * cos(currAngle) + center.x,
                                    radius * sin(currAngle) + center.y, 0);
        vertices.push_back(VertexFormat(point, color));
    }

    Mesh *circle = new Mesh(name);

    std::vector<unsigned short> indices;

    if (!fill) {
        circle->SetDrawMode(GL_LINE_LOOP);

        for (int i = 0; i < fragments; ++i) {
            indices.push_back(i);
        }
    } else {
        int centerPos = (int)(vertices.size());
        vertices.push_back(VertexFormat(center, color));

        for (int i = 0; i < fragments - 1; ++i) {
            indices.push_back(i);
            indices.push_back(centerPos);
            indices.push_back(i + 1);
        }

        indices.push_back(fragments - 1);
        indices.push_back(centerPos);
        indices.push_back(0);
    }

    circle->InitFromData(vertices, indices);
    return circle;
}
