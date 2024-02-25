#include "WanderAlt.h"
#include <iostream>
#include <random>
#include <vector>

#include "SteeringData.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Sprite.h"
#include "Arrive.h"
#include "Kinematic.h"
#include "Face.h"
#include "LookWhereYoureGoing.h"

WanderAlt::WanderAlt(Kinematic* targetInput, Sprite* characterInput) : Arrive(targetInput, characterInput) {
    //Align::setTargetRadius(0);
}

WanderAlt::~WanderAlt() {

}

void WanderAlt::execute(float timeDelta) {
    SteeringData* sd = calculateAccelerationPointer();
    std::cout << "sd->linear" << std::endl;
    std::cout << sd->linear.x << ", " << sd->linear.y << std::endl;

    if (sd != nullptr) {
        character->update(*sd, timeDelta);
    }
}

float WanderAlt::getRandNumZeroOne() {
    std::random_device rd;
    std::mt19937 mt(rd());
    
    // Create a uniform real distribution between 0 and 1.
    std::uniform_real_distribution<float> dist(0.0, 1.0);

    return dist(mt);
}

float WanderAlt::generateRandomBinomial() {
    return getRandNumZeroOne() - getRandNumZeroOne();
}

sf::Vector2f WanderAlt::convertAngleToVector(float angleInDegrees) {
    float angleInRadians = angleInDegrees * M_PI / 180.0;
    float x = std::cos(angleInRadians);
    float y = std::sin(angleInRadians);
    return sf::Vector2f(x, y);
}

SteeringData WanderAlt::calculateAcceleration() {
    return SteeringData();
}

SteeringData* WanderAlt::calculateAccelerationPointer() {
    // TODO Implement
    SteeringData* result = new SteeringData();

    wanderOrientation += generateRandomBinomial() * wanderRate;
    float targetOrientation = wanderOrientation + character->getDirection();

    std::cout << "targetOrientation" << std::endl;
    std::cout << targetOrientation << std::endl;

    sf::Vector2f targetPosition = character->getPosition() + wanderOffset * convertAngleToVector(character->getDirection());
    targetPosition += wanderRadius * convertAngleToVector(targetOrientation);

    sf::Vector2f directionVect = targetPosition - character->getPosition();
    sf::Vector2f targetVelocity = directionVect;
    normalizeVector(targetVelocity);
    targetVelocity *= targetSpeed;

    sf::Vector2f resultLinear = targetVelocity - character->getVelocityVector();
    resultLinear /= timeToTarget;

    if (getLengthOfVector(resultLinear) > maxAcceleration) {
        normalizeVector(resultLinear);
        resultLinear *= maxAcceleration;
    }

    target = new Kinematic(targetPosition, targetOrientation, targetVelocity, 0.0f);

    Arrive arriveBehavior(target, character);
    SteeringData* resultLinearFromArrive = arriveBehavior.calculateAccelerationPointer();

    LookWhereYoureGoing lookAheadBehavior(target, character);
    SteeringData* resultAngularLookAhead = lookAheadBehavior.calculateAccelerationPointer();
    if (resultLinearFromArrive != nullptr) {
        result->setLinear(resultLinearFromArrive->getLinear());
    } else {
        result->setLinear(sf::Vector2f(0.0f, 0.0f));
    }
    if (resultAngularLookAhead != nullptr) {
        result->setAngular(resultAngularLookAhead->getAngular());
    } else {
        result->setAngular(0.0f);
    }

    return result;
}

// ... rest of the Wander class implementation ...
