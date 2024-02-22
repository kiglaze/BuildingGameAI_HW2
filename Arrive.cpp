#include "SteeringData.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include "Sprite.h"
#include "Arrive.h"
#include <iostream>

Arrive::Arrive(Kinematic* targetInput, Sprite* characterInput)
: target(targetInput), character(characterInput) { // Use initializer list here
}

Arrive::~Arrive() {

}

void Arrive::execute(float timeDelta) {
    // Implementation for position-changing behavior
    SteeringData sd = calculateAcceleration();
    float x = sd.linear.x;
    float y = sd.linear.y;
    character->setVelocityVector(x, y);
    //std::cout << character.getVelocityVector().x << std::endl;
    //std::cout << character.getVelocityVector().y << std::endl;
    character->moveWithVelocityVector(timeDelta);
}

SteeringData Arrive::calculateAcceleration() {
    SteeringData steering;

    sf::Vector2f direction = target->getPosition() - character->getPosition();
    float distance = getLengthOfVector(direction);
    
    float targetSpeed;
    if (distance < targetRadius) {
        return SteeringData(sf::Vector2f(0.0f, 0.0f), 0.0f);
    }
    if (distance > slowRadius) {
        targetSpeed = maxSpeed;
    } else {
        // In slow radius
        targetSpeed = maxSpeed * (distance / slowRadius);
    }

    // Desired velocity
    sf::Vector2f targetVelocity = direction;
    normalizeVector(targetVelocity);
    targetVelocity *= targetSpeed;



    // Assuming we have access to the current velocity of the object, which is not shown here
    steering.linear = targetVelocity - character->getVelocityVector();
    steering.linear /= timeToTarget;

    if (getLengthOfVector(steering.linear) > maxAcceleration) {
        normalizeVector(steering.linear);
        steering.linear *= maxAcceleration;
    }



    steering.angular = 0; // Assuming no angular acceleration for simplicity

    return steering;
}


