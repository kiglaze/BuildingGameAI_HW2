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

class Wander : public Align {
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

private:
    float wanderOffset = 20;
    float wanderRadius = 35;
    float wanderRate = 50;
    float wanderOrientation = 0.0f; // This could start at any value
    float maxAcceleration = 2;
};

#endif // WANDER_H