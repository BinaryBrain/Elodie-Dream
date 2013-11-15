#ifndef ELODIE_H
#define ELODIE_H

#include "Entity.h"
#include "../Sprite/ElodieSprite.h"
#include "../Item/Item.h"


class Elodie : public Entity
{
public:
    Elodie();
    Elodie(sf::Vector2f position);
    Elodie(float x, float y);
    ElodieSprite* getSprite();
    virtual ~Elodie();

    sf::Vector2f* getPosition();

    void walkDown();
    void walkUp();
    void walkRight();
    void walkLeft();

    void stand();
    void move();
    void setDistanceToMove(float dist);
    bool isMoving();
    bool hasToMove();
    void noMoves();

    void update(sf::Time deltaTime);

    int getImmersionLevel();
    int getNightmareLevel();
protected:

private:
    void init();

    void walk();

    ElodieSprite* sprite;

    int centerX = 21;
    int centerY = 32;

    float toMove = 0;
    float speed = 0.3;
    bool goingUp = false;
    bool goingDown = false;
    bool goingRight = false;
    bool goingLeft = false;

    int immersionLevel = 100;
    int nightmareLevel = 50; // Max: 100

    std::vector<Item> stuff;
};

#endif // ELODIE_H
