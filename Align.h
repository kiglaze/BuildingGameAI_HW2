#ifndef ALIGN_H
#define ALIGN_H

#include "SteeringData.h"
#include <SFML/Graphics.hpp>
#include "SteeringBehavior.h"
#include "Sprite.h" // Make sure this exists and is correctly implemented

class Align : public SteeringBehavior {
public:
    // Constructor with initialization list
    Align(Kinematic* target, Sprite* character);

    // Override the virtual destructor
    virtual ~Align();

    float mapToRange(float rotation);

    // Override execute() method from SteeringBehavior
    void execute(float timeDelta) override;

    // Override calculateAcceleration() method from SteeringBehavior
    SteeringData calculateAcceleration() override;

    // Override calculateAcceleration() method from SteeringBehavior
    SteeringData* calculateAccelerationPointer() override;

protected:
    Kinematic* target;
    Sprite* character;

private:
    // Private member variables
    float maxAngularAcceleration = .02;
    float maxRotation = 0.1;
    float targetRadius = 15;
    float slowRadius = 45;
    float timeToTarget = 3;
};

#endif // ALIGN_H
