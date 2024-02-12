#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
class PositionBehavior : public SteeringBehavior {
public:
    void execute() override {
        // Implementation for position-changing behavior
    }

    sf::Vector2f calculateForce() override {
        // Calculate the influence on position, might return a desired position or a direction vector
        return sf::Vector2f(/* calculations */);
    }
};
