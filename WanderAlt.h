#ifndef WANDER_ALT_H
#define WANDER_ALT_H

#include "Wander.h"
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

class WanderAlt : public Arrive {
public:
    WanderAlt(Kinematic *targetInput, Sprite *characterInput);

    // Override the virtual destructor
    virtual ~WanderAlt();

    void execute(float timeDelta) override;

    float getRandNumZeroOne();

    float generateRandomBinomial();

    sf::Vector2f convertAngleToVector(float angleInDegrees);

    // Override calculateAcceleration() method from SteeringBehavior
    SteeringData calculateAcceleration() override;

    SteeringData* calculateAccelerationPointer() override;

private:
    float wanderOffset = 90;
    float wanderRadius = 85;
    float wanderRate = 70;
    float wanderOrientation = 0.0f; // This could start at any value
    float maxAcceleration = 0.005f;
    float targetSpeed = 0.001f;
    float timeToTarget = 2000.0f;
};

#endif // WANDER_ALT_H

