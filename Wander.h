#ifndef WANDER_H
#define WANDER_H

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
#include "Face.h"

class Wander : public Face {
public:
    Wander(Kinematic *targetInput, Sprite *characterInput);

    // Override the virtual destructor
    virtual ~Wander();

    void execute(float timeDelta) override;

    float getRandNumZeroOne();

    float generateRandomBinomial();

    sf::Vector2f convertAngleToVector(float angleInDegrees);

    // Override calculateAcceleration() method from SteeringBehavior
    SteeringData calculateAcceleration() override;

    SteeringData* calculateAccelerationPointer() override;

private:
    float wanderOffset = 20;
    float wanderRadius = 105;
    float wanderRate = 70;
    float wanderOrientation = 0.0f; // This could start at any value
    float maxAcceleration = 0.05f;
    float targetSpeed = 1.0f;
    float timeToTarget = 1.0f;
};

#endif // WANDER_H
