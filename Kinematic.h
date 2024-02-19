// Kinematic.h
#ifndef KINEMATIC_H
#define KINEMATIC_H

#include <SFML/Graphics.hpp>

class Kinematic {
public:
    sf::Vector2f position;
    float orientation;
    sf::Vector2f velocity;
    float rotation;

    Kinematic(sf::Vector2f pos, float orient, sf::Vector2f vel, float rot) {
        position = pos;
        orientation = orient;
        velocity = vel;
        rotation = rot;
    }

    // The update function takes values directly to set the member variables
    void update(sf::Vector2f positionVal, float orientationVal, sf::Vector2f velocityVal, float rotationVal);
};

#endif // KINEMATIC_H
