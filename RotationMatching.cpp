#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
class RotationMatching : public SteeringBehavior {
public:
    void execute() override {
        // Implementation for rotation-changing behavior
    }

    sf::Vector2f calculateForce() override {
        // This might return a vector that somehow represents rotational change, though the exact implementation depends on your system
        return sf::Vector2f();
    }
    // Method for scalar outcome
    float calculateRotationChange() {
        // Calculate and return the rotation change
    }
};
