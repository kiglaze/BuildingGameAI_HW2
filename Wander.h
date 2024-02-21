#ifndef WANDER_H
#define WANDER_H

#include "Align.h"

class Wander : public Align {
public:
    Wander(Kinematic* targetInput, Sprite* characterInput);

    // Override the virtual destructor
    virtual ~Wander();

    // Override execute() method from SteeringBehavior
    void execute(float timeDelta) override;

    // Override calculateAcceleration() method from SteeringBehavior
    SteeringData calculateAcceleration() override;

private:
    Kinematic* target;
    Sprite* character;
    float wanderOffset;
    float wanderRadius;
    float wanderRate;
    float wanderOrientation = 0.0f; // This could start at any value
    float maxAcceleration;
};

#endif // WANDER_H
