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
    //sd.linear = sf::Vector2f(-0.014, -0.014);

    character->update(sd, timeDelta);
    std::cout << "CHARACTER POS AFTER EXECUTE IN ARRIVE: " << std::endl;
    std::cout << character->getPosition().x << ", " << character->getPosition().y << std::endl;
 
}

/* void Arrive::execute(float timeDelta) {
    SteeringData result = calculateAcceleration();
    sf::Vector2f newPosVect = (character->getPosition()) + (character->getVelocityVector() * timeDelta);
    character->setPosition(newPosVect.x, newPosVect.y);

    character->setDirection(character->getDirection() + (character->getAngularVelocity() * timeDelta));

    sf::Vector2f newVelVect = character->getVelocityVector() + (result.linear * timeDelta);
    character->setVelocityVector(newVelVect.x, newVelVect.y);

    float newAngularVelocity = character->getAngularVelocity() + (result.angular * timeDelta);

    character->setAngularVelocity(newAngularVelocity);
} */

SteeringData Arrive::calculateAcceleration() {
    SteeringData result = SteeringData();
    sf::Vector2f directionVect = target->getPosition() - character->getPosition();
    float dirVectAng = atan2(directionVect.y, directionVect.x) * (180.0 / M_PI);
    std::cout << "dirVectAng" << std::endl;
    std::cout << dirVectAng << std::endl;
    float distance = getLengthOfVector(directionVect);
    if (distance < targetRadius) {
        return SteeringData(sf::Vector2f(0.0f, 0.0f), 0.0f);
    }

    float targetSpeed;
    if (distance > slowRadius) {
        targetSpeed = maxSpeed;
    } else {
        // In slow radius
        targetSpeed = maxSpeed * (distance / slowRadius);
    }

    // Desired velocity
    sf::Vector2f targetVelocity = directionVect;
    normalizeVector(targetVelocity);
    targetVelocity *= targetSpeed;

    // Assuming we have access to the current velocity of the object, which is not shown here
    result.linear = targetVelocity - character->getVelocityVector();
    result.linear /= timeToTarget;

    if (getLengthOfVector(result.linear) > maxAcceleration) {
        normalizeVector(result.linear);
        result.linear *= maxAcceleration;
    }

    result.angular = 0; // Assuming no angular acceleration for simplicity

    return result;
}


