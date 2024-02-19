#ifndef ARRIVE_H
#define ARRIVE_H

#include "SteeringData.h"
#include <SFML/Graphics.hpp>
#include "SteeringBehavior.h"
#include "Sprite.h" // Make sure this exists and is correctly implemented

class Arrive : public SteeringBehavior {
public:
    // Constructor with initialization list
    Arrive(const Sprite& target, const Sprite& character);

    // Override the virtual destructor
    virtual ~Arrive();

    // Override execute() method from SteeringBehavior
    void execute(float timeDelta) override;

    // Override calculateAcceleration() method from SteeringBehavior
    SteeringData calculateAcceleration() override;

private:
    // Private member variables
    Sprite target;
    Sprite character;
    float maxSpeed = 500;
    float targetRadius = 10;
    float slowRadius = 50;
    float maxAcceleration = 0;
    float timeToTarget = 0.1;
};

#endif // ARRIVE_H
