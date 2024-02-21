#include "Wander.h"
#include <random>

Wander::Wander(Kinematic* targetInput, Sprite* characterInput) 
: Align(targetInput, characterInput) {
}

Wander::~Wander() {

}

void Wander::execute(float timeDelta) {
    // TODO implement
}

SteeringData Wander::calculateAcceleration() {
    // TODO Implement
    return SteeringData(sf::Vector2f(0.0f, 0.0f), 0);
}

// ... rest of the Wander class implementation ...
