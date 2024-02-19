#ifndef STEERING_DATA_H
#define STEERING_DATA_H

#include <SFML/Graphics.hpp>

class SteeringData {
public:
    sf::Vector2f linear;  // Linear velocity or direction
    float angular;        // Angular velocity or direction

    // Default constructor
    SteeringData() : linear(0.0f, 0.0f), angular(0.0f) {}

    // Parameterized constructor for easy initialization
    SteeringData(sf::Vector2f lin, float ang) : linear(lin), angular(ang) {}
};

#endif // STEERING_DATA_H
