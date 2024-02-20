#include "SteeringData.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include "Sprite.h"
#include "Align.h"
#include <iostream>

Align::Align(Sprite* targetInput, Sprite* characterInput)
: target(targetInput), character(characterInput) { // Use initializer list here
}

Align::~Align() {

}

void Align::execute(float timeDelta) {
    // Implementation for position-changing behavior
    SteeringData sd = calculateAcceleration();
    //sd.angular = .3;
    std::cout << "sd.angular" << std::endl;
    std::cout << sd.angular << std::endl;
    character->setAngularVelocity(sd.angular);
    float angleToRotate = timeDelta * character->getAngularVelocity();
    float newAngleDirection = character->getDirection() + angleToRotate;
    character->setDirection(newAngleDirection);
    character->setRotation(newAngleDirection);
}

SteeringData Align::calculateAcceleration() {
    SteeringData steering;
    sf::Vector2f direction = target->getPosition() - character->getPosition();
    float directionLength = sqrt(pow(direction.x, 2) + pow(direction.y, 2));
    if (directionLength > 0) {

    }

    float targetOrientation = atan2(direction.x, direction.y) * (180.0 / M_PI);
    target->setDirection(targetOrientation);
    target->setRotation(targetOrientation);

    float rotation = target->getDirection() - character->getDirection();
    std::cout << character->getDirection() << std::endl;
    // Map the result to the (-pi, pi) interval.
    rotation = rotation * (M_PI / 180.0);

    float rotationSize = abs(rotation);
    if (rotationSize < targetRadius) {
        steering.angular = 0;
    } else {
        float targetRotation;
        if (rotationSize > slowRadius) {
            targetRotation = maxRotation;
        } else {
            targetRotation = maxRotation * rotationSize / slowRadius;
        }

        targetRotation *= rotation / rotationSize;

        steering.angular = targetRotation - character->getDirection();
        steering.angular /= timeToTarget;

        float angularAcceleration = abs(steering.angular);
        if (angularAcceleration > maxAngularAcceleration) {
            steering.angular /= angularAcceleration;
            steering.angular *= maxAngularAcceleration;
        }
    }
    // todo implement the rest.

    steering.linear = sf::Vector2f(0.0f, 0.0f);
    //steering.angular = 0; // Assuming no angular acceleration for simplicity
    return steering;
}


