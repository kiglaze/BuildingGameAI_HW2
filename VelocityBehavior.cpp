#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
class VelocityBehavior : public SteeringBehavior {
public:
    void execute() override {
        // Implementation for velocity-changing behavior
    }

    sf::Vector2f calculateForce() override {
        // Directly calculates the change or desired velocity
        return sf::Vector2f(/* calculations */);
    }
};
