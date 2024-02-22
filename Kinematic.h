// Kinematic.h
#ifndef KINEMATIC_H
#define KINEMATIC_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

class Kinematic {
public:
    Kinematic(sf::Vector2f pos, float orient, sf::Vector2f vel, float rot);

    sf::Vector2f getPosition() const;
    void setPosition(float posX, float posY);
    float getDirection() const;
    float mapToRange(float rotation);
    void setDirection(float newDirection);
    sf::Vector2f getVelocityVector() const;
    void setVelocityVector(float velX, float velY);
    float getAngularVelocity() const;
    void setAngularVelocity(float w);
    void update(sf::Vector2f positionVal, float orientationVal, sf::Vector2f velocityVal, float rotationVal);
private:
    sf::Vector2f position;
    float direction; // orientation
    sf::Vector2f velocity;
    float angular_velocity; // rotation
};

#endif // KINEMATIC_H
