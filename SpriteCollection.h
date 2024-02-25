#ifndef SPRITECOLLECTION_H
#define SPRITECOLLECTION_H

#include <vector>
#include "Sprite.h"

class SpriteCollection {
public:
    void addSprite(Sprite* sprite);
    void removeSprite(Sprite* sprite);
    void drawAll(sf::RenderWindow& window);
    std::size_t getSpriteCount();
    void addStartingSprite(std::string textureFilePath, int isLeader);
    const std::vector<Sprite*>& getSprites() const;
    sf::Vector2f getCOMPosition();
    float getCOMOrientation();
    sf::Vector2f getCOMVelocityVector();
    void deleteMarkedSprites();

private:
    std::vector<Sprite*> sprites;
};

#endif // SPRITECOLLECTION_H
