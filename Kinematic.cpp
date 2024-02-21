#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include "Kinematic.h"

// Constructor with member initializer list
Kinematic::Kinematic(sf::Vector2f pos, float orient, sf::Vector2f vel, float rot)
: position(pos), direction(orient), velocity(vel), angular_velocity(rot) {}

// Get the position vector of the sprite.
sf::Vector2f Kinematic::getPosition() const {
    return position;
}

// Set the position. 0, 0 is top left of the window. down is positive y. right is positive x.
void Kinematic::setPosition(float posX, float posY) {
    position = sf::Vector2f(posX, posY);
}

// Get direction. 0 = right. 90 = down. 180 = left. 270 = up.
float Kinematic::getDirection() const {
    return direction;
}

// Set direction of the sprite. 0 = right. 90 = down. 180 = left. 270 = up.
void Kinematic::setDirection(float newDirection) {
    direction = newDirection;
}

sf::Vector2f Kinematic::getVelocityVector() const {
    return velocity;
}

void Kinematic::setVelocityVector(float velX, float velY) {
    velocity.x = velX;
    velocity.y = velY;
}

float Kinematic::getAngularVelocity() const {
    return angular_velocity;
}

void Kinematic::setAngularVelocity(float w) {
    angular_velocity = w;
}

void Kinematic::update(sf::Vector2f positionVal, float orientationVal, sf::Vector2f velocityVal, float rotationVal) {
    position = positionVal;
    direction = orientationVal;
    velocity = velocityVal;
    angular_velocity = rotationVal;
}
