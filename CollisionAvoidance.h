#ifndef COLLISION_AVOIDANCE_H
#define COLLISION_AVOIDANCE_H

#include "SteeringData.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include "Sprite.h"
#include <iostream>
#include "SteeringBehavior.h"

class CollisionAvoidance : public SteeringBehavior {

public: 
    CollisionAvoidance(std::vector<Kinematic*> targets, Sprite* character);
    virtual ~CollisionAvoidance();
    void execute(float timeDelta) override;
    SteeringData calculateAcceleration();
    SteeringData* calculateAccelerationPointer() override;

protected:
    std::vector<Kinematic*> targets;
    Sprite* character;

private:
    float maxAcceleration = 0.0003;
    float collisionRadius = 180;
};

#endif
