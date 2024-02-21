#include "Sprite.h"
#include <iostream>
#include <vector>
#include <cmath>

// Constructor
Sprite::Sprite(const std::string& textureFile, float posX, float posY, int isLeader) {
    if (!texture.loadFromFile(textureFile)) {
        std::cerr << "Error loading texture" << std::endl;
    }

    velocity = sf::Vector2f(0, 0);
    angular_velocity = 0.0f;

    sprite.setTexture(texture);
    // Set the origin of the sprite to its center.
    sprite.setOrigin(getSpriteWidth() / 2.0f, getSpriteHeight() / 2.0f);
    sprite.setPosition(posX, posY);
    direction = 0;
    has_started = 0;
    has_reached_corner = 0;
    is_leader = isLeader;
    should_delete = 0;

    // Get the original size of the texture.
    sf::Vector2u textureSize = texture.getSize();

    // Setting the sprite size to 50x50 pixels. Involves setting the scale.
    float desiredWidth = 50.0f;
    float desiredHeight = 50.0f;
    float scaleX = desiredWidth / textureSize.x;
    float scaleY = desiredHeight / textureSize.y;
    sprite.setScale(scaleX, scaleY);
}

sf::Vector2f Sprite::getVelocityVector() {
    return velocity;
}

float Sprite::getSpriteWidth() {
    sf::Vector2u textureSize = texture.getSize();
    sf::Vector2f scale = sprite.getScale();
    return textureSize.x * scale.x;
}

float Sprite::getSpriteHeight() {
    sf::Vector2u textureSize = texture.getSize();
    sf::Vector2f scale = sprite.getScale();
    return textureSize.y * scale.y;
}

void Sprite::move(float dx, float dy) {
    sprite.move(dx, dy);
    setHasStarted(1);
}

void Sprite::moveRight(float diff) {
    sprite.move(diff, 0.0f);
}

void Sprite::moveDown(float diff) {
    sprite.move(0.0f, diff);
}

void Sprite::moveLeft(float diff) {
    sprite.move(-1 * diff, 0.0f);
}

void Sprite::moveUp(float diff) {
    sprite.move(0.0f, -1 * diff);
}

void Sprite::setScale(float scaleX, float scaleY) {
    sprite.setScale(scaleX, scaleY);
}

void Sprite::setVelocityVector(float velX, float velY) {
    velocity.x = velX;
    velocity.y = velY;
}

// Draw the sprite to the window.
void Sprite::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

// Get the position vector of the sprite.
sf::Vector2f Sprite::getPosition() const {
    return sprite.getPosition();
}

void Sprite::turnRight() {
    direction = fmod((direction + 90), 360);
    sprite.rotate(90);
}

// Get direction. 0 = right. 90 = down. 180 = left. 270 = up.
float Sprite::getDirection() {
    return direction;
}

// Set direction of the sprite. 0 = right. 90 = down. 180 = left. 270 = up.
void Sprite::setDirection(float newDirection) {
    direction = newDirection;
}

// Set the position. 0, 0 is top left of the window. down is positive y. right is positive x.
void Sprite::setPosition(float posX, float posY) {
    sprite.setPosition(posX, posY);
}

// Rotate the sprite clockwise by the specified number of degrees.
void Sprite::rotate(float x) {
    sprite.rotate(x);
}

void Sprite::setRotation(float x) {
    sprite.setRotation(x);
}

float Sprite::getRotation() {
    return sprite.getRotation();
}

float Sprite::getAngularVelocity() {
    return angular_velocity;
}

void Sprite::setAngularVelocity(float w) {
    angular_velocity = w;
}

int Sprite::getHasStarted() {
    return has_started;
}

void Sprite::setHasStarted(int hasStartedVal) {
    has_started = hasStartedVal;
}

int Sprite::getHasReachedCorner() {
    return has_reached_corner;
}

int Sprite::getIsLeader() {
    return is_leader;
}

void Sprite::markForDeletion() {
    should_delete = 1;
}

int Sprite::shouldBeDeleted() {
    return should_delete;
}

void Sprite::moveWithVelocityVector(float timeDelta) {
    sprite.move(timeDelta * getVelocityVector().x, timeDelta * getVelocityVector().y);
}

// Move the sprite in the direction of the "direction" attribute.
void Sprite::moveAccordingToDirection(float timeDelta, float screenWidth, float screenHeight) {
    //float velocityRatioShortEdge = (screenHeight/screenWidth);
    float horizontalVelocity = 0.2;
    //float verticalVelocity = horizontalVelocity * velocityRatioShortEdge;
    //float numPixels = timeDelta * verticalVelocity;

    float vX = cos(getDirection() * (M_PI / 180.0)) * horizontalVelocity;
    float vY = sin(getDirection() * (M_PI / 180.0)) * horizontalVelocity;
    setVelocityVector(vX, vY);

    sprite.move(timeDelta * getVelocityVector().x, timeDelta * getVelocityVector().y);
}

// Rotate the sprite 90 degrees counterclockwise once it reaches a corner of the window.
void Sprite::rotateIfNeeded(float screenWidth, float screenHeight) {
    float maxWindowX = screenWidth;
    // Window height is 3/4 of width.
    float maxWindowY = screenHeight;
    float innerXMaxOffsetLoc = maxWindowX - (getSpriteWidth()/2);
    float innerYMaxOffsetLoc = maxWindowY - (getSpriteHeight()/2);

    // Get the position of the sprite
    sf::Vector2f position = getPosition();

    if (position.x >= innerXMaxOffsetLoc && position.y <= (getSpriteHeight()/2)) {
        setDirection(90);
        setRotation(90);
        has_reached_corner = 1;
    } else if (position.x >= innerXMaxOffsetLoc && position.y >= innerYMaxOffsetLoc) {
        setDirection(180);
        setRotation(180);
        has_reached_corner = 1;
    } else if (position.x <= (getSpriteWidth()/2) && position.y >= innerYMaxOffsetLoc) {
        setDirection(270);
        setRotation(270);
        has_reached_corner = 1;
    } else if (position.x <= (getSpriteWidth()/2) && position.y <= (getSpriteHeight()/2) && getHasStarted() == 1) {
        setDirection(0);
        setRotation(0);
        has_reached_corner = 1;
        // Delete the sprites that are marked for deletion.
        markForDeletion();
    } else {
        has_reached_corner = 0;
    }
}
