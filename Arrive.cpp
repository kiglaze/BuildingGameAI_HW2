#include "SteeringData.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include "Sprite.h"
#include "Arrive.h"
#include <iostream>

Arrive::Arrive(const Sprite& targetInput, const Sprite& characterInput)
: target(targetInput), character(characterInput) { // Use initializer list here
}

Arrive::~Arrive() {

}

void Arrive::execute(float timeDelta) {
    // Implementation for position-changing behavior
    std::cout << "asdf" << std::endl;
    SteeringData sd = calculateAcceleration();
    float x = sd.linear.x;
    float y = sd.linear.y;
    //std::cout << x << std::endl;
    //std::cout << y << std::endl;
    //character.setVelocityVector(x, y);
    character.setVelocityVector(-3.5, -3.5);
    //std::cout << character.getVelocityVector().x << std::endl;
    //std::cout << character.getVelocityVector().y << std::endl;
    character.moveWithVelocityVector(timeDelta);
    //std::cout << character.getPosition().x << std::endl;
    //std::cout << character.getPosition().y << std::endl;
}

SteeringData Arrive::calculateAcceleration() {
    SteeringData steering;

    sf::Vector2f direction = target.getPosition() - character.getPosition();
    float distance = sqrt(pow(direction.x, 2) + pow(direction.y, 2));
    
    float targetSpeed;
    if (distance < targetRadius) {
        targetSpeed = 0;
    } else if (distance > slowRadius) {
        targetSpeed = maxSpeed;
    } else {
        // In slow radius
        targetSpeed = maxSpeed * (distance / slowRadius);
    }

    // Desired velocity
    sf::Vector2f desiredVelocity = direction;
    if (distance != 0) { // Normalize direction if not zero
        desiredVelocity /= distance;
    }
    desiredVelocity *= targetSpeed;

    sf::Vector2f currentVelocity = character.getVelocityVector();
    // Assuming we have access to the current velocity of the object, which is not shown here
    steering.linear = desiredVelocity - currentVelocity;
    steering.angular = 0; // Assuming no angular acceleration for simplicity

    return steering;
}


