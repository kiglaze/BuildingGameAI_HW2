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
#include "WanderAlt.h"
#include "CollisionAvoidance.h"
#include "LookWhereYoureGoing.h"
#include "Crumb.h"

// Function to add a wall
void addWall(std::vector<sf::RectangleShape>& walls, const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color) {
    sf::RectangleShape wall(size);
    wall.setPosition(position);
    wall.setFillColor(color);
    walls.push_back(wall);
}

// @author Iris Glaze
int main()
{
    sf::Clock clock;
    float maxWindowX = 640.0;
    // Window height is 3/4 of width.
    float maxWindowY = 480.0;
    sf::RenderWindow window(sf::VideoMode(maxWindowX, maxWindowY), "SFML works!");
    
    std::vector<sf::RectangleShape> walls;
    float wallWidth = 10.0;

    // bottom-left room
    addWall(walls, sf::Vector2f(maxWindowX * 0.55, wallWidth), sf::Vector2f(10, maxWindowY - (wallWidth + 20)), sf::Color::Black);
    addWall(walls, sf::Vector2f(wallWidth, maxWindowX * 0.35), sf::Vector2f(10, maxWindowY - (wallWidth + 20) - (maxWindowX * 0.35)), sf::Color::Black);
    addWall(walls, sf::Vector2f(maxWindowX * 0.55, wallWidth), sf::Vector2f(10, maxWindowY - (wallWidth + 20) - (maxWindowX * 0.35)), sf::Color::Black);
    addWall(walls, sf::Vector2f(wallWidth, (maxWindowX * 0.35) + wallWidth), sf::Vector2f(10 + (maxWindowX * 0.55), maxWindowY - (wallWidth + 20) - (maxWindowX * 0.35)), sf::Color::Black);

    // top room
    addWall(walls, sf::Vector2f(maxWindowX * 0.70, wallWidth), sf::Vector2f(120, maxWindowY - (wallWidth + 20) - 225), sf::Color::Black);
    addWall(walls, sf::Vector2f(wallWidth, maxWindowX * 0.30), sf::Vector2f(120, maxWindowY - (wallWidth + 20) - (maxWindowX * 0.30) - 225), sf::Color::Black);
    addWall(walls, sf::Vector2f(maxWindowX * 0.70, wallWidth), sf::Vector2f(120, maxWindowY - (wallWidth + 20) - (maxWindowX * 0.30) - 225), sf::Color::Black);
    addWall(walls, sf::Vector2f(wallWidth, (maxWindowX * 0.30) + wallWidth), sf::Vector2f(120 + (maxWindowX * 0.70), maxWindowY - (wallWidth + 20) - (maxWindowX * 0.30) - 225), sf::Color::Black);

    // bottom-right room
    addWall(walls, sf::Vector2f(maxWindowX * 0.40, wallWidth), sf::Vector2f(370, maxWindowY - (wallWidth + 20)), sf::Color::Black);
    addWall(walls, sf::Vector2f(wallWidth, maxWindowX * 0.35), sf::Vector2f(370, maxWindowY - (wallWidth + 20) - (maxWindowX * 0.35)), sf::Color::Black);
    addWall(walls, sf::Vector2f(maxWindowX * 0.40, wallWidth), sf::Vector2f(370, maxWindowY - (wallWidth + 20) - (maxWindowX * 0.35)), sf::Color::Black);
    addWall(walls, sf::Vector2f(wallWidth, (maxWindowX * 0.35) + wallWidth), sf::Vector2f(370 + (maxWindowX * 0.40), maxWindowY - (wallWidth + 20) - (maxWindowX * 0.35)), sf::Color::Black);


    std::vector<Crumb> breadcrumbs = std::vector<Crumb>();
    for(int i = 0; i < 100; i++)
    {
        Crumb c(i);
        breadcrumbs.push_back(c);
    }

    // Variables to store the mouse positions
    sf::Vector2i previousMousePositionInt = sf::Mouse::getPosition(window);
    sf::Vector2f previousMousePosition = sf::Vector2f(static_cast<float>(previousMousePositionInt.x), static_cast<float>(previousMousePositionInt.y));
    sf::Vector2f currentMousePosition;
    // Variables to store the velocity
    sf::Vector2f mouseVelocity(0.f, 0.f);

    //SpriteCollection myCollection;
    SpriteCollection steeringCollection(&breadcrumbs);

    ////float numPixels = 1.0;
    // Frame counter
    int frameCounter = 0;
    std::string textureFilePath = "./sprite_high_res.png";

    //myCollection.addStartingSprite(textureFilePath, 1);

    Sprite* spriteA = new Sprite(textureFilePath, 125.f, 125.f, -55.0, sf::Vector2f(0, 0), 0, 0, &breadcrumbs); // no
    // set orientation of a Sprite
    Sprite* spriteB = new Sprite(textureFilePath, 275.f, 325.f, 0, sf::Vector2f(0, 0), 0, 0, &breadcrumbs);
    
    Sprite* spriteC = new Sprite(textureFilePath, 325.f, 225.f, -55.0, sf::Vector2f(0, 0), 0, 0, &breadcrumbs); // no
    Sprite* spriteD = new Sprite(textureFilePath, 375.f, 265.f, -55.0, sf::Vector2f(0, 0), 0, 0, &breadcrumbs); // no
    Sprite* spriteE = new Sprite(textureFilePath, 475.f, 195.f, -55.0, sf::Vector2f(0, 0), 0, 0, &breadcrumbs); // no
    Sprite* spriteF = new Sprite(textureFilePath, 575.f, 95.f, -55.0, sf::Vector2f(0, 0), 0, 0, &breadcrumbs); // no
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
    Wander* wanderObj = nullptr;
    Kinematic* wanderAltTargetObj = nullptr;
    WanderAlt* wanderAltObj = nullptr;
    
    bool isMatchingMouseVelocity = false;
    Kinematic* mouseMovementsKinObj = new Kinematic(currentMousePosition, 0.0f, sf::Vector2f(0.0f, 0.0f), 0.0f);

    bool isFlockingOn = false;

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
            sf::Time elapsed = clock.restart();
            float timeDelta = elapsed.asMilliseconds();
            if (timeDelta > 0) { // Check to prevent division by zero
                // Update current mouse position
                sf::Vector2i currentMousePosInt = sf::Mouse::getPosition(window);
                currentMousePosition = sf::Vector2f(static_cast<float>(currentMousePosInt.x), static_cast<float>(currentMousePosInt.y));

                // Calculate displacement
                sf::Vector2f displacement = currentMousePosition - previousMousePosition;
                // Calculate velocity: velocity = displacement / time
                // Note: This gives you velocity in pixels/time unit.
                mouseVelocity.x = displacement.x / timeDelta;
                mouseVelocity.y = displacement.y / timeDelta;

                if (mouseMovementsKinObj != nullptr) {
                    mouseMovementsKinObj->setPosition(currentMousePosition.x, currentMousePosition.y);
                    mouseMovementsKinObj->setVelocityVector(mouseVelocity.x, mouseVelocity.y);

                }

                // Update previous mouse position
                previousMousePosition = currentMousePosition;

            }

            // Reset frame counter
            frameCounter = 0;

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
                isMatchingMouseVelocity = false;
                isFlockingOn = false;
            }
            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::V)) {
                // Velocity matching to the mouse.
                isMatchingMouseVelocity = true;

            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
                isFlockingOn = true;
            }
            SteeringData* sdMouseVelMatchAndLook = nullptr;
            if (isMatchingMouseVelocity == true) {
                mouseFollowArriveBehavior = new VelocityMatching(mouseMovementsKinObj, spriteF);
                //Kinematic* blankKinematic = new Kinematic(sf::Vector2f(0, 0), 0, sf::Vector2f(0, 0), 0);
                LookWhereYoureGoing lookAheadBehavior(mouseMovementsKinObj, spriteF);
                mouseFollowArriveBehavior->execute(timeDelta);
                lookAheadBehavior.execute(timeDelta);
            }

            if (timeDelta > 0) {
                // Flocking implementation here.
                if (isFlockingOn) {
                    // getCOMPosition
                    sf::Vector2f comPosVect = steeringCollection.getCOMPosition();
                    sf::Vector2f comVelVect = steeringCollection.getCOMVelocityVector();
                    Kinematic* collectionCOMKinematic = new Kinematic(comPosVect, 0, comVelVect, 0);
                    for (Sprite* sprite : sprites) {
                        if (sprite == spriteF) {
                            continue;
                        }
                        Arrive goTowardsSprite(collectionCOMKinematic, sprite);
                        goTowardsSprite.execute(0.6 * timeDelta);
                        goTowardsSprite.setSlowRadius(120);
                        goTowardsSprite.setTargetRadius(70);

                        Face turnTowardsSprite(collectionCOMKinematic, sprite);
                        turnTowardsSprite.execute(timeDelta);

                        //VelocityMatching velMatchCOM(collectionCOMKinematic, sprite);
                        VelocityMatching velMatchCOM(collectionCOMKinematic, sprite);
                        velMatchCOM.setMaxAcceleration(.01);
                        velMatchCOM.execute(0.002 * timeDelta);
                    }
                    // C, D, E, G
                    int velocityMatchingWeight = 2;
                    CollisionAvoidance avoidCollisions(kinematics, spriteC);
                    avoidCollisions.execute(velocityMatchingWeight * timeDelta);
                    CollisionAvoidance avoidCollisions2(kinematics, spriteD);
                    avoidCollisions2.execute(velocityMatchingWeight * timeDelta);
                    CollisionAvoidance avoidCollisions3(kinematics, spriteE);
                    avoidCollisions3.execute(velocityMatchingWeight * timeDelta);
                    //CollisionAvoidance avoidCollisions4(kinematics, spriteF);
                    //avoidCollisions4.execute(timeDelta);
                    CollisionAvoidance avoidCollisions5(kinematics, spriteA);
                    avoidCollisions5.execute(velocityMatchingWeight * timeDelta);
                    CollisionAvoidance avoidCollisions6(kinematics, spriteB);
                    avoidCollisions6.execute(velocityMatchingWeight * timeDelta);

                    steeringCollection.allSpritesDropCrumbs();

                }

                if (kinemMouseClickObj != nullptr) {
                    Arrive arriveBehavior(kinemMouseClickObj, spriteB);
                    arriveBehavior.execute(timeDelta);
                    // std::cout << spriteB->getVelocityVector().x << ", " << spriteB->getVelocityVector().y << std::endl;

                    Face faceBehavior(kinemMouseClickObj, spriteB);
                    faceBehavior.execute(timeDelta);

                    spriteB->dropSomeCrumbs();
                }
                if (wanderTargetObj != nullptr) {
                    if (wanderObj == nullptr) {
                        wanderObj = new Wander(wanderTargetObj, spriteB);
                    }
                    wanderObj->execute(timeDelta);
                    spriteB->dropSomeCrumbs();
                }
                if (wanderAltTargetObj != nullptr) {
                    if (wanderAltObj == nullptr) {
                        wanderAltObj = new WanderAlt(wanderTargetObj, spriteB);
                    }
                    wanderAltObj->execute(timeDelta);
                    spriteB->dropSomeCrumbs();
                }
                if (mouseFollowArriveBehavior != nullptr) {
                    // VelocityMatch execute and look where going execute combined
                    if (sdMouseVelMatchAndLook != nullptr) {
                        spriteF->update(*sdMouseVelMatchAndLook, timeDelta);
                    }
                }
            }


            //myCollection.deleteMarkedSprites();
            steeringCollection.deleteMarkedSprites();
            
            if (mouseFollowArriveBehavior != nullptr) {
                delete mouseFollowArriveBehavior;
                mouseFollowArriveBehavior = nullptr;
            }
        }

        for(int i = 0; i < static_cast<int>(breadcrumbs.size()); i++) {
            breadcrumbs[i].draw(&window);
        }
        //myCollection.drawAll(window);
        steeringCollection.drawAll(window);
        // Draw all the walls
        for (const auto& wall : walls) {
            window.draw(wall);
        }
        window.display();
    }

    if (kinemMouseClickObj != nullptr) {
        delete kinemMouseClickObj;
        kinemMouseClickObj = nullptr; // To prevent dangling pointers
    }
    if (wanderTargetObj != nullptr) {
        delete wanderTargetObj;
        wanderTargetObj = nullptr;
    }
    if (wanderAltTargetObj != nullptr) {
        delete wanderAltTargetObj;
        wanderAltTargetObj = nullptr;
    }

    return 0;
}
