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
    //std::cout << sd.angular << std::endl;

    std::cout << "aligning..." << std::endl;
}

SteeringData Align::calculateAcceleration() {
    SteeringData steering;
    float rotation = target->getDirection() - character->getDirection();
    std::cout << character->getDirection() << std::endl;
    // Map the result to the (-pi, pi) interval.
    rotation = rotation * (M_PI / 180.0);
    float rotationSize = abs(rotation);
    //std::cout << rotationSize << std::endl;
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

        steering.angular = targetRotation - character->getRotation();
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


