#include "SteeringData.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include "Sprite.h"
#include "Arrive.h"
#include <iostream>
#include "VelocityMatching.h"

VelocityMatching::VelocityMatching(Kinematic* targetInput, Sprite* characterInput)
: target(targetInput), character(characterInput) { // Use initializer list here
}

VelocityMatching::~VelocityMatching() {

}

void VelocityMatching::setMaxAcceleration(float maxAccVal) {
    maxAcceleration = maxAccVal;
}

void VelocityMatching::execute(float timeDelta) {
    SteeringData* sd = calculateAccelerationPointer();

    if (sd != nullptr) {
        character->update(*sd, timeDelta);
    }
    bool isTargetMoving = target->getVelocityVector().x != 0 || target->getVelocityVector().y != 0;
    bool isCharacterMoving = character->getVelocityVector().x != 0 || character->getVelocityVector().y != 0;
    if (isTargetMoving == false && isCharacterMoving == true) {
        character->setVelocityVector(0, 0);
    }
}

SteeringData VelocityMatching::calculateAcceleration() {
    return SteeringData();
}

SteeringData* VelocityMatching::calculateAccelerationPointer() {
    SteeringData* result = new SteeringData();
    sf::Vector2f originalCharacterVelVect = sf::Vector2f(character->getVelocityVector());
    sf::Vector2f roundedCharacterVelVect = sf::Vector2f(round(originalCharacterVelVect.x), round(originalCharacterVelVect.y));

    float targetSpeed = getLengthOfVector(target->getVelocityVector());
    // Desired velocity
    sf::Vector2f targetVelocity = target->getVelocityVector();
    normalizeVector(targetVelocity);
    targetVelocity *= targetSpeed;

    // Assuming we have access to the current velocity of the object, which is not shown here
    sf::Vector2f resultLinear = targetVelocity - roundedCharacterVelVect;
    resultLinear /= timeToTarget;

    if (getLengthOfVector(resultLinear) > maxAcceleration) {
        normalizeVector(resultLinear);
        resultLinear *= maxAcceleration;
    }

    result->setLinear(resultLinear);

    result->setAngular(0);
    return result;
}


