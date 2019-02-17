#include "Rectangle.h"

using namespace BrickBreakerObjects;

Rectangle::Rectangle() {

}

Rectangle::Rectangle(glm::vec3 position, glm::vec3 color, float width, float height)
        : Entity(position, color){
    this->width = width;
    this->height = height;
}

Rectangle::~Rectangle() {

}

float Rectangle::GetWidth() {
    return width;
}

void Rectangle::SetWidth(float width) {
    this->width = width;
}

float Rectangle::GetHeight() {
    return height;
}