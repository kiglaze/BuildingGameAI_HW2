#ifndef ALIGN_H
#define ALIGN_H

#include "SteeringData.h"
#include <SFML/Graphics.hpp>
#include "SteeringBehavior.h"
#include "Sprite.h" // Make sure this exists and is correctly implemented

class Align : public SteeringBehavior {
public:
    // Constructor with initialization list
    Align(Sprite* target, Sprite* character);

    // Override the virtual destructor
    virtual ~Align();

    // Override execute() method from SteeringBehavior
    void execute(float timeDelta) override;

    // Override calculateAcceleration() method from SteeringBehavior
    SteeringData calculateAcceleration() override;

private:
    // Private member variables
    Sprite* target;
    Sprite* character;
    float maxAngularAcceleration = 0.3;
    float maxRotation = 0.3;
    float targetRadius = 35;
    float slowRadius = 60;
    float timeToTarget = 2;
};

#endif // ALIGN_H
