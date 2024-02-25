#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include "Sprite.h"
#include "SpriteCollection.h"
#include "Arrive.h"
#include "Align.h"
#include "Face.h"
#include "VelocityMatching.h"
#include "SteeringData.h"
#include "Kinematic.h"
#include "Wander.h"
#include "CollisionAvoidance.h"
#include "LookWhereYoureGoing.h"

// @author Iris Glaze
int main()
{
    sf::Clock clock;
    float maxWindowX = 640.0;
    // Window height is 3/4 of width.
    float maxWindowY = 480.0;
    sf::RenderWindow window(sf::VideoMode(maxWindowX, maxWindowY), "SFML works!");

    // Variables to store the mouse positions
    sf::Vector2i previousMousePositionInt = sf::Mouse::getPosition(window);
    sf::Vector2f previousMousePosition = sf::Vector2f(static_cast<float>(previousMousePositionInt.x), static_cast<float>(previousMousePositionInt.y));
    sf::Vector2f currentMousePosition;
    // Variables to store the velocity
    sf::Vector2f mouseVelocity(0.f, 0.f);

    //SpriteCollection myCollection;
    SpriteCollection steeringCollection;

    ////float numPixels = 1.0;
    // Frame counter
    int frameCounter = 0;
    std::string textureFilePath = "./sprite_high_res.png";

    //myCollection.addStartingSprite(textureFilePath, 1);

    Sprite* spriteA = new Sprite(textureFilePath, 125.f, 125.f, -55.0, sf::Vector2f(0, 0), 0, 0); // no
    //Sprite* spriteA = new Sprite(textureFilePath, 475.f, 125.f, 0); // yes
    //Sprite* spriteA = new Sprite(textureFilePath, 475.f, 375.f, 0); // yes
    //Sprite* spriteA = new Sprite(textureFilePath, 75.f, 375.f, 0); // no
    // set orientation of a Sprite
    Sprite* spriteB = new Sprite(textureFilePath, 275.f, 325.f, 0, sf::Vector2f(0, 0), 0, 0);
    
    Sprite* spriteC = new Sprite(textureFilePath, 325.f, 225.f, -55.0, sf::Vector2f(0, 0), 0, 0); // no
    Sprite* spriteD = new Sprite(textureFilePath, 375.f, 265.f, -55.0, sf::Vector2f(0, 0), 0, 0); // no
    Sprite* spriteE = new Sprite(textureFilePath, 475.f, 195.f, -55.0, sf::Vector2f(0, 0), 0, 0); // no
    Sprite* spriteF = new Sprite(textureFilePath, 575.f, 95.f, -55.0, sf::Vector2f(0, 0), 0, 0); // no
    //Sprite* spriteG = new Sprite(textureFilePath, 475.f, 105.f, -55.0, sf::Vector2f(0, 0), 0, 0); // no
    
    std::vector<Kinematic*> kinematics;
    std::vector<Sprite*> sprites;
    sprites.push_back(spriteC);
    sprites.push_back(spriteD);
    sprites.push_back(spriteE);
    sprites.push_back(spriteF);

    sprites.push_back(spriteA);
    sprites.push_back(spriteB);
    //sprites.push_back(spriteG);
    for (Sprite* sprite : sprites) {
        kinematics.push_back(sprite);
    }

    
    
    steeringCollection.addSprite(spriteA);
    steeringCollection.addSprite(spriteB);

    steeringCollection.addSprite(spriteC);
    steeringCollection.addSprite(spriteD);
    steeringCollection.addSprite(spriteE);
    steeringCollection.addSprite(spriteF);
    //steeringCollection.addSprite(spriteG);

    Kinematic* kinemMouseClickObj = nullptr;
    Kinematic* wanderTargetObj = nullptr;
    Kinematic* wanderAltTargetObj = nullptr;
    
    bool isMatchingMouseVelocity = false;
    Kinematic* mouseMovementsKinObj = new Kinematic(currentMousePosition, 0.0f, sf::Vector2f(0.0f, 0.0f), 0.0f);


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
            //if (myCollection.getSpriteCount() == 0) {
                //myCollection.addStartingSprite(textureFilePath, 1);
            //}

            sf::Time elapsed = clock.restart();
            float timeDelta = elapsed.asMilliseconds();
            //std::cout << timeDelta << std::endl;
            if (timeDelta > 0) { // Check to prevent division by zero
                // Update current mouse position
                sf::Vector2i currentMousePosInt = sf::Mouse::getPosition(window);
                currentMousePosition = sf::Vector2f(static_cast<float>(currentMousePosInt.x), static_cast<float>(currentMousePosInt.y));

                // Calculate displacement
                sf::Vector2f displacement = currentMousePosition - previousMousePosition;
                // Calculate velocity: velocity = displacement / time
                // Note: This gives you velocity in pixels/second if deltaTime is in seconds
                mouseVelocity.x = displacement.x / timeDelta;
                mouseVelocity.y = displacement.y / timeDelta;
                //std::cout << "mouseVelocity" << std::endl;
                //std::cout << mouseVelocity.x << ", " << mouseVelocity.y << std::endl;

                if (mouseMovementsKinObj != nullptr) {
                    mouseMovementsKinObj->setPosition(currentMousePosition.x, currentMousePosition.y);
                    mouseMovementsKinObj->setVelocityVector(mouseVelocity.x, mouseVelocity.y);

                    // sf::Vector2f mouseMvmtsVect = mouseMovementsKinObj->getVelocityVector();
                    // std::cout << "mouseMvmtsVect" << std::endl;
                    // std::cout << mouseMvmtsVect.x << ", " << mouseMvmtsVect.y << std::endl;
                }

                // Update previous mouse position
                previousMousePosition = currentMousePosition;

            }

            //const std::vector<Sprite*> allSprites = myCollection.getSprites();
/*             for (Sprite* sprite : allSprites) {
                if (sprite != nullptr) {
                    // Move sprite according to the direction attribute.
                    sprite->moveAccordingToDirection(timeDelta, maxWindowX, maxWindowY);
                    sprite->setHasStarted(1);
                }
            } */

            // Reset frame counter
            frameCounter = 0;
/*             for (Sprite* sprite : allSprites) {
                if (sprite != nullptr) {
                    // Rotate the sprite if it reaches a corner.
                    sprite->rotateIfNeeded(maxWindowX, maxWindowY);

                    // Add a new sprite when the leader sprite reaches a corner.
                    if (sprite->getHasReachedCorner() == 1 && sprite->getIsLeader() == 1 && sprite->shouldBeDeleted() == 0) {
                        myCollection.addStartingSprite(textureFilePath, 0);
                    }
                }
            } */


            // Activated by pressing "V" to have sprite velocity match the mouse.
            VelocityMatching* mouseFollowArriveBehavior = nullptr;
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                sf::Vector2i localPosition = sf::Mouse::getPosition(window);
                // If left mouse click, arrive and align to that spot.
                if (wanderTargetObj != nullptr) {
                    delete wanderTargetObj;
                    wanderTargetObj = nullptr;
                }
                if (wanderAltTargetObj != nullptr) {
                    delete wanderAltTargetObj;
                    wanderAltTargetObj = nullptr;
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
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                // If press "q", do 2nd type of wandering.
                if (wanderAltTargetObj == nullptr) {
                    if (kinemMouseClickObj != nullptr) {
                        delete kinemMouseClickObj;
                        kinemMouseClickObj = nullptr;
                    }
                    wanderAltTargetObj = new Kinematic(sf::Vector2f(0.0f, 0.0f), 0, sf::Vector2f(0, 0), 0);
                }
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                // If press "d", stop wandering.
                if (wanderTargetObj != nullptr) {
                    delete wanderTargetObj;
                    wanderTargetObj = nullptr;
                }
                if (wanderAltTargetObj != nullptr) {
                    delete wanderAltTargetObj;
                    wanderAltTargetObj = nullptr;
                }
            }
            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::V)) {
                // Velocity matching to the mouse.
                isMatchingMouseVelocity = true;

            }
            if (isMatchingMouseVelocity == true) {
                mouseFollowArriveBehavior = new VelocityMatching(mouseMovementsKinObj, spriteF);
            }

            if (timeDelta > 0) {
                // Flocking implementation here.
                if (true) {
                    Kinematic* blankKinematic = new Kinematic(sf::Vector2f(0, 0), 0, sf::Vector2f(0, 0), 0);
                    LookWhereYoureGoing lookAheadBehavior(blankKinematic, spriteF);
                    lookAheadBehavior.execute(timeDelta);
                    for (Sprite* sprite : sprites) {
                        if (sprite == spriteF) {
                            continue;
                        }
                        Arrive goTowardsSprite(spriteF, sprite);
                        goTowardsSprite.execute(timeDelta);

                        Face turnTowardsSprite(spriteF, sprite);
                        turnTowardsSprite.execute(timeDelta);
                    }
                    // C, D, E, G
                    CollisionAvoidance avoidCollisions(kinematics, spriteC);
                    avoidCollisions.execute(timeDelta);
                    CollisionAvoidance avoidCollisions2(kinematics, spriteD);
                    avoidCollisions2.execute(timeDelta);
                    CollisionAvoidance avoidCollisions3(kinematics, spriteE);
                    avoidCollisions3.execute(timeDelta);
                    /*
                    CollisionAvoidance avoidCollisions4(kinematics, spriteG);
                    avoidCollisions4.execute(timeDelta); */
                }

                if (kinemMouseClickObj != nullptr) {
                    Arrive arriveBehavior(kinemMouseClickObj, spriteB);
                    arriveBehavior.execute(timeDelta);
                    // std::cout << spriteB->getVelocityVector().x << ", " << spriteB->getVelocityVector().y << std::endl;

                    Face faceBehavior(kinemMouseClickObj, spriteB);
                    faceBehavior.execute(timeDelta);

                    //Align alignBehavior(kinemMouseClickObj, spriteB);
                    //alignBehavior.execute(timeDelta);
                }
                if (wanderTargetObj != nullptr) {
                    Wander wanderObj(wanderTargetObj, spriteB);
                    wanderObj.execute(timeDelta);
                }
                if (wanderAltTargetObj != nullptr) {
                    Wander wanderAltObj(wanderAltTargetObj, spriteB);
                    wanderAltObj.execute(timeDelta);
                }
                if (mouseFollowArriveBehavior != nullptr) {
                    sf::Vector2f mousemovementsVect = mouseMovementsKinObj->getVelocityVector();
                    std::cout << "mousemovementsVect" << std::endl;
                    std::cout << mousemovementsVect.x << ", " << mousemovementsVect.y << std::endl;
                    mouseFollowArriveBehavior->execute(timeDelta);
                }
            }

            //myCollection.deleteMarkedSprites();
            steeringCollection.deleteMarkedSprites();
        }

        //myCollection.drawAll(window);
        steeringCollection.drawAll(window);
        window.display();
    }

    delete spriteA;
    delete spriteB;

    return 0;
}
