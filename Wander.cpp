#include "Wander.h"
#include <iostream>
#include <random>
#include <vector>

#include "SteeringData.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Sprite.h"
#include "Align.h"
#include "Kinematic.h"


Wander::Wander(Kinematic* targetInput, Sprite* characterInput) : Align(targetInput, characterInput) {
    std::cout << "test" << std::endl;
}

Wander::~Wander() {

}

void Wander::execute(float timeDelta) {
    SteeringData sd = calculateAcceleration();

    float x = sd.linear.x;
    float y = sd.linear.y;
    character->setVelocityVector(x, y);
    character->moveWithVelocityVector(timeDelta);

    character->setAngularVelocity(sd.angular);
    float angleToRotate = timeDelta * character->getAngularVelocity();
    float newAngleDirection = character->getDirection() + angleToRotate;
    character->setDirection(newAngleDirection);
    character->setRotation(newAngleDirection);
}

float Wander::getRandNumZeroOne() {
    std::random_device rd;
    std::mt19937 mt(rd());
    
    // Create a uniform real distribution between 0 and 1.
    std::uniform_real_distribution<float> dist(0.0, 1.0);

    return dist(mt);
}

float Wander::generateRandomBinomial() {
    return getRandNumZeroOne() - getRandNumZeroOne();
}

sf::Vector2f Wander::convertAngleToVector(float angleInDegrees) {
    float angleInRadians = angleInDegrees * M_PI / 180.0;
    float x = std::cos(angleInRadians);
    float y = std::sin(angleInRadians);
    return sf::Vector2f(x, y);
}

SteeringData Wander::calculateAcceleration() {
    // TODO Implement
    SteeringData result;
    wanderOrientation += generateRandomBinomial() + wanderRate;
    float targetOrientation = wanderOrientation + character->getDirection();
    target->setDirection(targetOrientation);
    sf::Vector2f targetPosition = character->getPosition() + wanderOffset * convertAngleToVector(character->getDirection());
    targetPosition += wanderRadius * convertAngleToVector(targetOrientation);
    target->setPosition(targetPosition.x, targetPosition.y);

    result = Align::calculateAcceleration();
    result.linear = maxAcceleration * convertAngleToVector(character->getDirection());
    
    return result;
}

// ... rest of the Wander class implementation ...
