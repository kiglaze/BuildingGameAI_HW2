#ifndef VELOCITYMATCHING_H
#define VELOCITYMATCHING_H

#include "Kinematic.h" // Assuming Kinematic is defined in its own header file
#include "Sprite.h" // Assuming Sprite is defined in its own header file
#include "SteeringData.h" // Assuming SteeringData is a struct or class defined elsewhere
#include "SteeringBehavior.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <iostream>

class VelocityMatching : public SteeringBehavior {
private:
    Kinematic* target; // Pointer to the target Kinematic object
    Sprite* character; // Pointer to the character Sprite object

protected:
    float timeToTarget = 0.1; // set to 0.1
    float maxAcceleration = 0.03;
    //float maxAcceleration = 0.005;
    //float maxAcceleration = 0.09;
    //float maxAcceleration = 0.9;

public:
    // Constructor
    VelocityMatching(Kinematic* targetInput, Sprite* characterInput);

    // Destructor
    ~VelocityMatching();

    void setMaxAcceleration(float maxAccVal);

    // Method to execute the velocity matching behavior
    void execute(float timeDelta) override;

    // Method to calculate acceleration for velocity matching
    SteeringData calculateAcceleration() override;

    SteeringData* calculateAccelerationPointer() override;
};

#endif // VELOCITYMATCHING_H
