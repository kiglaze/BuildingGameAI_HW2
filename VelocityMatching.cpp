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
    // Implementation for position-changing behavior
    SteeringData sd = calculateAcceleration();
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


