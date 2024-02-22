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

protected:
    Kinematic* target;
    Sprite* character;

private:
    // Private member variables
    float maxAngularAcceleration = .2;
    float maxRotation = 360;
    float targetRadius = 15;
    float slowRadius = 45;
    float timeToTarget = 3;
};

#endif // ALIGN_H
