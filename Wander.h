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

    void updateWanderOrientation(float wanderOrientationValue);

    sf::Vector2f convertAngleToVector(float angleInDegrees);

    // Override calculateAcceleration() method from SteeringBehavior
    SteeringData calculateAcceleration() override;

    SteeringData* calculateAccelerationPointer() override;

private:
    float wanderOffset = 305;
    float wanderRadius = 295;
    float wanderRate = 70;
    float maxAcceleration = 0.0005f;
    float targetSpeed = 0.10f;
    float timeToTarget = 1.0f;
    float wanderOrientation = -10.0f; // This could start at any value
};

#endif // WANDER_H
