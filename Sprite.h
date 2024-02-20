#ifndef SPRITE_H
#define SPRITE_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class SpriteCollection; // Forward declaration if SpriteCollection is used

class Sprite {
public:
    Sprite(const std::string& textureFile, float posX, float posY, int isLeader);

    sf::Vector2f getVelocityVector();
    float getSpriteWidth();
    float getSpriteHeight();

    void move(float dx, float dy);
    void moveRight(float diff);
    void moveDown(float diff);
    void moveLeft(float diff);
    void moveUp(float diff);

    void setScale(float scaleX, float scaleY);
    void setVelocityVector(float velX, float velY);
    void draw(sf::RenderWindow& window);
    sf::Vector2f getPosition() const;
    void setPosition(float posX, float posY);

    void setDirection(int newDirection);
    void turnRight();
    int getDirection();

    void rotate(float x);
    void setRotation(float x);
    float getRotation();
    float getAngularVelocity();
    void setAngularVelocity(float w);

    int getHasStarted();
    void setHasStarted(int hasStartedVal);

    int getHasReachedCorner();
    int getIsLeader();
    void markForDeletion();
    int shouldBeDeleted();

    void moveWithVelocityVector(float timeDelta);
    void moveAccordingToDirection(float timeDelta, float screenWidth, float screenHeight);
    void rotateIfNeeded(float screenWidth, float screenHeight);

private:
    sf::Texture texture;
    sf::Sprite sprite;
    int direction;
    float angular_velocity;
    int has_started;
    int has_reached_corner;
    int is_leader;
    int should_delete;
    sf::Vector2f velocity;
};

#endif // SPRITE_H
