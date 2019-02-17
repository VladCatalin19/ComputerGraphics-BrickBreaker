#pragma once

#include <Core/World.h>

/**
 * This namespace contains the names of all the objects used in a scene. it is
 * used not to create conflicts with other classes with the same name.
 */
namespace BrickBreakerObjects {
    class Entity;
    class Circle;
    class Rectangle;
    class Square;
    class Ball;
    class Lives;
    class Wall;
    class Brick;
    class Platform;
    class PowerUp;
}

/**
 * This class implemets the entity of the scenes. An entity is any object from
 * the scenes, it provides a position and a color of the object.
 */
class BrickBreakerObjects::Entity {
public:
    Entity();
    Entity(glm::vec3 position, glm::vec3 color);
    ~Entity();

    glm::vec3 GetPosition();
    void SetPosition(glm::vec3 position);
    glm::vec3 GetColor();
    void SetColor(glm::vec3 color);

private:
    glm::vec3 position;
    glm::vec3 color;
};