#ifndef ARRIVE_H
#define ARRIVE_H

#include "SteeringData.h"
#include <SFML/Graphics.hpp>
#include "SteeringBehavior.h"
#include "Sprite.h" // Make sure this exists and is correctly implemented

class Arrive : public SteeringBehavior {
public:
    // Constructor with initialization list
    Arrive(Sprite* target, Sprite* character);

    // Override the virtual destructor
    virtual ~Arrive();

    // Override execute() method from SteeringBehavior
    void execute(float timeDelta) override;

    // Override calculateAcceleration() method from SteeringBehavior
    SteeringData calculateAcceleration() override;

private:
    // Private member variables
    Sprite* target;
    Sprite* character;
    float maxSpeed = 0.3;
    float targetRadius = 35;
    float slowRadius = 60;
    float maxAcceleration = 0;
    float timeToTarget = 2;
};

#endif // ARRIVE_H