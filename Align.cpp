#include "SteeringData.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include "Sprite.h"
#include "Align.h"
#include <iostream>

Align::Align(Kinematic* targetInput, Sprite* characterInput) {
    target = targetInput;
    character = characterInput;
    std::cout << "test" << std::endl;
}

Align::~Align() {

}

float Align::mapToRange(float rotation) {
    // Normalize the rotation to the range [-180, 180]
    rotation = fmod(rotation, 360.0f);
    if (rotation > 180.0f) {
        rotation -= 360.0f;
    } else if (rotation < -180.0f) {
        rotation += 360.0f;
    }
    return rotation;
}

void Align::execute(float timeDelta) {
    std::cout << "MAPPING TO RANGE: " << std::endl;
    std::cout << mapToRange(45.5649) << std::endl;
    std::cout << mapToRange(-279.975) << std::endl;
    std::cout << mapToRange(-279.975) << std::endl;
    std::cout << mapToRange(-500.975) << std::endl;
    std::cout << mapToRange(500.33) << std::endl;
    std::cout << mapToRange(0) << std::endl;
    // Implementation for position-changing behavior
    SteeringData sd = calculateAcceleration();
    //sd.angular = .3;
    //std::cout << "sd.angular" << std::endl;
    //std::cout << sd.angular << std::endl;
    character->setAngularVelocity(sd.angular);
    float angleToRotate = timeDelta * character->getAngularVelocity();
    std::cout << "angleToRotate" << std::endl;
    std::cout << angleToRotate << std::endl;
    float newAngleDirection = character->getDirection() + angleToRotate;
    character->setDirection(newAngleDirection);
    character->setRotation(newAngleDirection);
    std::cout << "--------------" << std::endl;
}

SteeringData Align::calculateAcceleration() {
    
    sf::Vector2f direction = target->getPosition() - character->getPosition();
    float directionLength = sqrt(pow(direction.x, 2) + pow(direction.y, 2));
    if (directionLength == 0) {
        return SteeringData(sf::Vector2f(0.0f, 0.0f), 0.0f);
    }

    //std::cout << "direction.x" << std::endl;
    //std::cout << direction.x << std::endl;
    //std::cout << "direction.y" << std::endl;
    //std::cout << direction.y << std::endl;
    float targetOrientation = atan2(direction.y, direction.x) * (180.0 / M_PI);
    target->setDirection(targetOrientation);

    SteeringData steering;
    float rotation = mapToRange(target->getDirection() - character->getDirection());

    std::cout << "target->getDirection()" << std::endl;
    std::cout << target->getDirection() << std::endl;
    std::cout << "character->getDirection()" << std::endl;
    std::cout << character->getDirection() << std::endl;
    // Map the result to the (-pi, pi) interval.
    //rotation = rotation * (M_PI / 180.0);

    float rotationSize = fabs(rotation);
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
            //std::cout << "maxRotation" << std::endl;
            //std::cout << maxRotation << std::endl;
            //std::cout << "rotationSize" << std::endl;
            //std::cout << rotationSize << std::endl;
            //std::cout << "slowRadius" << std::endl;
            //std::cout << slowRadius << std::endl;
            //std::cout << "targetRotation" << std::endl;
            //std::cout << targetRotation << std::endl;
            // TODO: may be getting stuck here?
        }

        targetRotation *= rotation / rotationSize;
        std::cout << "targetRotation" << std::endl;
        std::cout << targetRotation << std::endl;

        steering.angular = targetRotation - character->getDirection();

        std::cout << "character->getDirection()" << std::endl;
        std::cout << character->getDirection() << std::endl;

        std::cout << "steering.angular" << std::endl;
        std::cout << steering.angular << std::endl;

        steering.angular /= timeToTarget;

        std::cout << "steering.angular" << std::endl;
        std::cout << steering.angular << std::endl;

        float angularAcceleration = fabs(steering.angular);
        if (angularAcceleration > maxAngularAcceleration) {
            steering.angular /= angularAcceleration;
            steering.angular *= maxAngularAcceleration;
        }
        std::cout << "steering.angular" << std::endl;
        std::cout << steering.angular << std::endl;
    }
    // todo implement the rest.

    steering.linear = sf::Vector2f(0.0f, 0.0f);
    //steering.angular = 0; // Assuming no angular acceleration for simplicity
    return steering;
}


