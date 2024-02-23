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

void VelocityMatching::execute(float timeDelta) {
    SteeringData sd = calculateAcceleration();
    sf::Vector2f newPosVect = (character->getPosition()) + (character->getVelocityVector() * timeDelta);
    character->setPosition(newPosVect.x, newPosVect.y);

    character->setDirection(character->getDirection() + (character->getAngularVelocity() * timeDelta));

    sf::Vector2f newVelVect = character->getVelocityVector() + (sd.linear * timeDelta);
    character->setVelocityVector(newVelVect.x, newVelVect.y);

    float newAngularVelocity = character->getAngularVelocity() + (sd.angular * timeDelta);

    character->setAngularVelocity(newAngularVelocity);
}

SteeringData VelocityMatching::calculateAcceleration() {
    SteeringData result;
    result.linear = target->getVelocityVector() - character->getVelocityVector();
    result.linear /= timeToTarget;
    float resultLinearLength = getLengthOfVector(result.linear);
    if (resultLinearLength > maxAcceleration) {
        normalizeVector(result.linear);
        result.linear *= maxAcceleration;
    }

    result.angular = 0;
    return result;
}


