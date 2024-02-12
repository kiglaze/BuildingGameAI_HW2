#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

class SteeringBehavior {
public:
    // Virtual destructor to ensure derived class destructors are called
    virtual ~SteeringBehavior() {}

    // Pure virtual function for executing the behavior
    virtual void execute() = 0;

    // Additional pure virtual functions as needed
    // For example, you might want a function to calculate the force based on this behavior
    virtual sf::Vector2f calculateForce() = 0;
};
