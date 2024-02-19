#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

class Kinematic {
public:
    sf::Vector2f position;
    float orientation;
    sf::Vector2f velocity;
    float rotation;

    Kinematic(sf::Vector2f pos, float orient, sf::Vector2f vel, float rot) {
        position = pos;
        orientation = orient;
        velocity = vel;
        rotation = rot;
    }

    void update(sf::Vector2f positionVal, float orientationVal, sf::Vector2f velocityVal, float rotationVal) {
        position = positionVal;
        orientation = orientationVal;
        velocity = velocityVal;
        rotation = rotationVal;
    }
};
