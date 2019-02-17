#include "Circle.h"

using namespace BrickBreakerObjects;

Circle::Circle() {

}

Circle::Circle(glm::vec3 position, glm::vec3 color, float radius) 
        : Entity(position, color){
    this->radius = radius;
}

Circle::~Circle() {

}

float Circle::GetRadius() {
    return radius;
}

void Circle::SetRadius(float radius) {
    this->radius = radius;
}