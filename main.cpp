#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include "Sprite.h"
#include "SpriteCollection.h"

// @author Iris Glaze
int main()
{
    float maxWindowX = 640.0;
    // Window height is 3/4 of width.
    float maxWindowY = 480.0;
    sf::RenderWindow window(sf::VideoMode(maxWindowX, maxWindowY), "SFML works!");

    SpriteCollection myCollection;

    float numPixels = 1.0;
    // Frame counter
    int frameCounter = 0;
    std::string textureFilePath = "./sprite_high_res.png";

    myCollection.addStartingSprite(textureFilePath, 1);


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

            const std::vector<Sprite*> allSprites = myCollection.getSprites();

            for (Sprite* sprite : allSprites) {
                if (sprite != nullptr) {
                    // Move sprite according to the direction attribute.
                    sprite->moveAccordingToDirection(numPixels, maxWindowX, maxWindowY);
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
            myCollection.deleteMarkedSprites();
        }

        myCollection.drawAll(window);
        window.display();
    }

    return 0;
}
