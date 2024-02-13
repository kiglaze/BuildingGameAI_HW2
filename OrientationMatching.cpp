#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
class OrientationMatching : public SteeringBehavior {
public:
    void execute() override {
        // Implementation for orientation-changing behavior
    }

    sf::Vector2f calculateForce() override {
        // This method might return a vector that influences orientation change
        return sf::Vector2f(/* calculations */);
    }
};
