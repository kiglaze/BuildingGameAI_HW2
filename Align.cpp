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
    if (directionLength == 0) {
        return SteeringData(sf::Vector2f(0.0f, 0.0f), 0.0f);
    }

    std::cout << "direction.x" << std::endl;
    std::cout << direction.x << std::endl;
    std::cout << "direction.y" << std::endl;
    std::cout << direction.y << std::endl;
    std::cout << "atan2(direction.x, direction.y)" << std::endl;
    std::cout << atan2(direction.x, direction.y) << std::endl;
    float targetOrientation = atan2(direction.x, direction.y) * (180.0 / M_PI);
    std::cout << "targetOrientation" << std::endl;
    std::cout << targetOrientation << std::endl;
    target->setDirection(targetOrientation);
    target->setRotation(targetOrientation);

    float rotation = target->getDirection() - character->getDirection();

    std::cout << "target->getDirection()" << std::endl;
    std::cout << target->getDirection() << std::endl;
    std::cout << "character->getDirection()" << std::endl;
    std::cout << character->getDirection() << std::endl;
    // Map the result to the (-pi, pi) interval.
    //rotation = rotation * (M_PI / 180.0);

    float rotationSize = abs(rotation);
    if (rotationSize < targetRadius) {
        std::cout << "A" << std::endl;
        steering.angular = 0;
    } else {
        float targetRotation;
        if (rotationSize > slowRadius) {
            std::cout << "B" << std::endl;
            targetRotation = maxRotation;
        } else {
            std::cout << "C" << std::endl;

            targetRotation = maxRotation * rotationSize / slowRadius;
            std::cout << "maxRotation" << std::endl;
            std::cout << maxRotation << std::endl;
            std::cout << "rotationSize" << std::endl;
            std::cout << rotationSize << std::endl;
            std::cout << "slowRadius" << std::endl;
            std::cout << slowRadius << std::endl;
            std::cout << "targetRotation" << std::endl;
            std::cout << targetRotation << std::endl;
            // TODO: may be getting stuck here?
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


