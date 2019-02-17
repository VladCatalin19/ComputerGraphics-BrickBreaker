#include "Square.h"

using namespace BrickBreakerObjects;

Square::Square() {

}

Square::Square(glm::vec3 position, glm::vec3 color, float length)
        : Entity(position, color){
    this->length = length;
}

Square::~Square() {

}

float Square::GetLength() {
    return length;
}