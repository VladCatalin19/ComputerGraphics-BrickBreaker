#include "Entity.h"

using namespace BrickBreakerObjects;

Entity::Entity() {
    position = glm::vec3(0.0f, 0.0f, 0.0f);
    color = glm::vec3(0.0f, 0.0f, 0.0f);
}

Entity::Entity(glm::vec3 position, glm::vec3 color) {
    this->position = position;
    this->color = color;
}

Entity::~Entity() {

}

glm::vec3 Entity::GetPosition() {
    return position;
}

void Entity::SetPosition(glm::vec3 position) {
    this->position = position;
}

glm::vec3 Entity::GetColor() {
    return color;
}

void Entity::SetColor(glm::vec3 color) {
    this->color = color;
}