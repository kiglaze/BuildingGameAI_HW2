#include "SteeringData.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include "Kinematic.h"
#include "Sprite.h"
#include "CollisionAvoidance.h"
#include <iostream>

CollisionAvoidance::CollisionAvoidance(std::vector<Kinematic*> targetsInput, Sprite* characterInput)
: targets(targetsInput), character(characterInput) { // Initializer list.
}

CollisionAvoidance::~CollisionAvoidance() {

}

void CollisionAvoidance::execute(float timeDelta) {
    SteeringData* sd = calculateAccelerationPointer();
    if (sd != nullptr) {
        character->update(*sd, timeDelta);
    }
}

SteeringData CollisionAvoidance::calculateAcceleration() {
    return SteeringData();
}

SteeringData* CollisionAvoidance::calculateAccelerationPointer() {
    SteeringData* result = new SteeringData();

    float shortestTime = INFINITY;
    Kinematic* firstTarget = nullptr;
    float firstMinSeparation = 65.0f;
    float firstDistance = 67.0f;
    sf::Vector2f firstRelativePos = sf::Vector2f(60.0f, 80.0f);
    sf::Vector2f firstRelativeVelocity = sf::Vector2f(10.0f, 10.0f);
    // A for loop to loop through all the Kinematic target pointers.
    for (auto& target : targets) {
        if (target == character) {
            continue;
        }
        // Calculate the time to collision.
        sf::Vector2f relativePos = target->getPosition() - character->getPosition();
        sf::Vector2f relativeVel = target->getVelocityVector() - character->getVelocityVector();
        float relativeSpeed = getLengthOfVector(relativeVel);
        float timeToCollisionNumerator = (relativePos.x * relativeVel.x + relativePos.y * relativeVel.y);
        float timeToCollisionDenominator = (relativeSpeed * relativeSpeed);
        if (timeToCollisionNumerator == 0 && timeToCollisionDenominator == 0) {
            continue;
        }
        float timeToCollision = (timeToCollisionNumerator / timeToCollisionDenominator);
        
        // Check if there is going to be a collision at all.
        std::cout << "COLLISION?!?!" << std::endl;
        float distance = getLengthOfVector(relativePos);
        float minSeparation = distance - (relativeSpeed * timeToCollision);
        if (minSeparation > (2 * collisionRadius)) {
            continue;
        }
        std::cout << "XXXXXXX" << std::endl;
        // Check if it is the shortest.
        std::cout << "timeToCollisionNumerator: " << timeToCollisionNumerator << "; timeToCollision: " << timeToCollision << "; ... shortestTime: " << shortestTime << std::endl;
        if (timeToCollision > 0 && timeToCollision < shortestTime) {
            shortestTime = timeToCollision;
            firstTarget = target;
            firstMinSeparation = minSeparation;
            firstDistance = distance;
            firstRelativePos = relativePos;
            firstRelativeVelocity = relativeVel;
            std::cout << "YYYYYYYY" << std::endl;
        }
    }
    // 2 - Calculate the steering.
    if (firstTarget == nullptr) {
        delete result;
        result = nullptr;
        return result; 
    }
    // If we're going to hit exactly, or if we're already colliding, then do the steering based on current position.
    sf::Vector2f relativePos;
    if ((firstMinSeparation < 0) || (firstDistance < 2 * collisionRadius)) {
        relativePos = firstTarget->getPosition() - character->getPosition();
    } else {
        relativePos = firstRelativePos + firstRelativeVelocity * shortestTime;
    }
    normalizeVector(relativePos);
    result->setLinear(relativePos * maxAcceleration);
    std::cout << "result.linear: " << result->getLinear().x << ", " << result->getLinear().y << std::endl;
    result->setAngular(0);
    return result;
}

