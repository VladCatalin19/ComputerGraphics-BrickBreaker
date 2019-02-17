#include "Platform.h"
#include <algorithm>

using namespace BrickBreakerObjects;

Platform::Platform() {

}

Platform::Platform(glm::vec3 position, glm::vec3 color, float width, float height)
        : Rectangle(position, color, width, height) {

}

Platform::~Platform() {

}

void Platform::SetPosition(glm::vec3 position) {
    Entity::SetPosition(position);
}

void Platform::SetPosition(glm::vec3 position, float wallsThickness, float resolutionX) {
    float minX = wallsThickness;
    float maxX = resolutionX - (wallsThickness + GetWidth());
    float x = std::min(std::max(position.x, minX), maxX);
    float y = GetPosition().y;
    Entity::SetPosition(glm::vec3(x, y, 0.0f));
}