#include "Sprite.h"
#include <iostream>

// Constructor
Sprite::Sprite(const std::string& textureFile, float posX, float posY, int isLeader) {
    if (!texture.loadFromFile(textureFile)) {
        std::cerr << "Error loading texture" << std::endl;
    }

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

// Draw the sprite to the window.
void Sprite::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

// Get the position vector of the sprite.
sf::Vector2f Sprite::getPosition() const {
    return sprite.getPosition();
}

void Sprite::turnRight() {
    direction = (direction + 90) % 360;
    sprite.rotate(90);
}

// Get direction. 0 = right. 90 = down. 180 = left. 270 = up.
int Sprite::getDirection() {
    return direction;
}

// Set direction of the sprite. 0 = right. 90 = down. 180 = left. 270 = up.
void Sprite::setDirection(int newDirection) {
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

// Move the sprite in the direction of the "direction" attribute.
void Sprite::moveAccordingToDirection(float numPixels, float screenWidth, float screenHeight) {
    float velocityRatioShortEdge = (screenHeight/screenWidth);
    if (getDirection() == 0) {
        // Right: Move the sprite
        moveRight(numPixels); // Example: move right by 10 pixels
    } else if (getDirection() == 90) {
        // Down: Move the sprite
        moveDown(numPixels * velocityRatioShortEdge); // Example: move right by 10 pixels
    } else if (getDirection() == 180) {
        // Left: Move the sprite
        moveLeft(numPixels); // Example: move right by 10 pixels
    } else if (getDirection() == 270) {
        // Up: Move the sprite
        moveUp(numPixels * velocityRatioShortEdge); // Example: move right by 10 pixels
    }
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
        rotate(90);
        setDirection(90);
        has_reached_corner = 1;
    } else if (position.x >= innerXMaxOffsetLoc && position.y >= innerYMaxOffsetLoc) {
        rotate(90);
        setDirection(180);
        has_reached_corner = 1;
    } else if (position.x <= (getSpriteWidth()/2) && position.y >= innerYMaxOffsetLoc) {
        rotate(90);
        setDirection(270);
        has_reached_corner = 1;
    } else if (position.x <= (getSpriteWidth()/2) && position.y <= (getSpriteHeight()/2) && getHasStarted() == 1) {
        rotate(90);
        setDirection(0);
        has_reached_corner = 1;
        // Delete the sprites that are marked for deletion.
        markForDeletion();
    } else {
        has_reached_corner = 0;
    }
}
