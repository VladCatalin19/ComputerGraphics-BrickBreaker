#include "Wall.h"

using namespace BrickBreakerObjects;

Wall::Wall() {

}

Wall::Wall(glm::vec3 position, glm::vec3 color, float width, float height)
        : Rectangle(position, color, width, height) {

}

Wall::~Wall() {

}