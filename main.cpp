#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include "Sprite.h"
#include "SpriteCollection.h"
#include "Arrive.h"
#include "Align.h"
#include "SteeringData.h"
#include "Kinematic.h"
#include "Wander.h"

// @author Iris Glaze
int main()
{
    sf::Clock clock;
    float maxWindowX = 640.0;
    // Window height is 3/4 of width.
    float maxWindowY = 480.0;
    sf::RenderWindow window(sf::VideoMode(maxWindowX, maxWindowY), "SFML works!");

    // Variables to store the mouse positions
    sf::Vector2i previousMousePosition = sf::Mouse::getPosition(window);
    sf::Vector2i currentMousePosition;
    // Variables to store the velocity
    sf::Vector2f mouseVelocity(0.f, 0.f);

    SpriteCollection myCollection;
    SpriteCollection steeringCollection;

    ////float numPixels = 1.0;
    // Frame counter
    int frameCounter = 0;
    std::string textureFilePath = "./sprite_high_res.png";

    myCollection.addStartingSprite(textureFilePath, 1);

    Sprite* spriteA = new Sprite(textureFilePath, 125.f, 125.f, 0, sf::Vector2f(0, 0), 0, 0); // no
    //Sprite* spriteA = new Sprite(textureFilePath, 475.f, 125.f, 0); // yes
    //Sprite* spriteA = new Sprite(textureFilePath, 475.f, 375.f, 0); // yes
    //Sprite* spriteA = new Sprite(textureFilePath, 75.f, 375.f, 0); // no
    // set orientation of a Sprite
    Sprite* spriteB = new Sprite(textureFilePath, 275.f, 325.f, 0, sf::Vector2f(0, 0), 0, 0);
    steeringCollection.addSprite(spriteA);
    steeringCollection.addSprite(spriteB);
    Kinematic* kinemMouseClickObj = nullptr;
    Kinematic* wanderTargetObj = nullptr;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Increment frame counter
        frameCounter++;

        window.clear(sf::Color(200, 0, 0, 255));

        int frameCountMark = 10;

        // Check if 100 frames have passed
        if (frameCounter >= frameCountMark)
        {
            // Adding a new leader sprite as soon as there are zero sprites.
            if (myCollection.getSpriteCount() == 0) {
                myCollection.addStartingSprite(textureFilePath, 1);
            }

            sf::Time elapsed = clock.restart();
            float timeDelta = elapsed.asMilliseconds();
            //std::cout << timeDelta << std::endl;

            // Update current mouse position
            currentMousePosition = sf::Mouse::getPosition(window);

            // Calculate displacement
            sf::Vector2i displacement = currentMousePosition - previousMousePosition;

            // Calculate velocity: velocity = displacement / time
            // Note: This gives you velocity in pixels/second if deltaTime is in seconds
            if (timeDelta > 0) { // Check to prevent division by zero
                mouseVelocity.x = static_cast<float>(displacement.x) / timeDelta;
                mouseVelocity.y = static_cast<float>(displacement.y) / timeDelta;
                std::cout << "--------------" << std::endl;
                std::cout << "mouseVelocity.x" << std::endl;
                std::cout << mouseVelocity.x << std::endl;
                std::cout << "mouseVelocity.y" << std::endl;
                std::cout << mouseVelocity.y << std::endl;
                std::cout << "--------------" << std::endl;
            }

            // Update previous mouse position
            previousMousePosition = currentMousePosition;

            const std::vector<Sprite*> allSprites = myCollection.getSprites();
            for (Sprite* sprite : allSprites) {
                if (sprite != nullptr) {
                    // Move sprite according to the direction attribute.
                    sprite->moveAccordingToDirection(timeDelta, maxWindowX, maxWindowY);
                    sprite->setHasStarted(1);
                }
            }

            // Reset frame counter
            frameCounter = 0;
            for (Sprite* sprite : allSprites) {
                if (sprite != nullptr) {
                    // Rotate the sprite if it reaches a corner.
                    sprite->rotateIfNeeded(maxWindowX, maxWindowY);

                    // Add a new sprite when the leader sprite reaches a corner.
                    if (sprite->getHasReachedCorner() == 1 && sprite->getIsLeader() == 1 && sprite->shouldBeDeleted() == 0) {
                        myCollection.addStartingSprite(textureFilePath, 0);
                    }
                }
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                sf::Vector2i localPosition = sf::Mouse::getPosition(window);
                // If left mouse click, arrive and align to that spot.
                if (wanderTargetObj != nullptr) {
                    delete wanderTargetObj;
                    wanderTargetObj = nullptr;
                }
                if (kinemMouseClickObj != nullptr) {
                    delete kinemMouseClickObj;
                    kinemMouseClickObj = nullptr;
                }
                kinemMouseClickObj = new Kinematic(sf::Vector2f(localPosition.x, localPosition.y), 0, sf::Vector2f(0, 0), 0);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                // If press "w", start wandering.
                if (wanderTargetObj == nullptr) {
                    if (kinemMouseClickObj != nullptr) {
                        delete kinemMouseClickObj;
                        kinemMouseClickObj = nullptr;
                    }
                    wanderTargetObj = new Kinematic(sf::Vector2f(0.0f, 0.0f), 0, sf::Vector2f(0, 0), 0);
                }
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                // If press "d", stop wandering.
                if (wanderTargetObj != nullptr) {
                    delete wanderTargetObj;
                    wanderTargetObj = nullptr;
                }
            }
            
            if (kinemMouseClickObj != nullptr) {
                Arrive arriveBehavior(kinemMouseClickObj, spriteB);
                arriveBehavior.execute(timeDelta);

                Align alignBehavior(kinemMouseClickObj, spriteB);
                alignBehavior.execute(timeDelta);
            }
            if (wanderTargetObj != nullptr) {
                Wander wanderObj(wanderTargetObj, spriteB);
                wanderObj.execute(timeDelta);
            }

            myCollection.deleteMarkedSprites();
        }

        myCollection.drawAll(window);
        steeringCollection.drawAll(window);
        window.display();
    }

    delete spriteA;
    delete spriteB;

    return 0;
}
