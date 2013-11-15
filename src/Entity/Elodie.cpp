#include "Elodie.h"

Elodie::Elodie()
{
    this->init();
}

Elodie::Elodie(sf::Vector2f position)
{
    this->init();
    this->sprite->setPosition(position.x-centerX, position.y-centerY);
}

Elodie::Elodie(float x, float y)
{
    this->init();
    this->sprite->setPosition(x-centerX, y-centerY);
}

ElodieSprite* Elodie::getSprite()
{
    return this->sprite;
}

Elodie::~Elodie()
{
    //  TODO : maybe source of memory leak
    //  delete this->sprite;
}

sf::Vector2f* Elodie::getPosition()
{
    return new sf::Vector2f(this->sprite->getPosition().x+centerX,this->sprite->getPosition().y+centerY);
}

void Elodie::stand()
{
    this->sprite->stand();
}

void Elodie::move()
{
    if (goingDown)
    {
        toMove -= speed;
        this->sprite->move(0, speed);
    }
    else if (goingLeft)
    {
        toMove -= speed;
        this->sprite->move(-speed, 0);
    }
    else if (goingRight)
    {
        toMove -= speed;
        this->sprite->move(+speed, 0);
    }
    else if (goingUp)
    {
        toMove -= speed;
        this->sprite->move(0, -speed);
    }
    else
    {
        noMoves();
    }
}

void Elodie::walkDown()
{
    this->walk();
    goingDown = true;
}
void Elodie::walkUp()
{
    this->walk();
    goingUp = true;
}
void Elodie::walkRight()
{
    this->walk();
    goingRight = true;
}
void Elodie::walkLeft()
{
    this->walk();
    goingLeft = true;
}

void Elodie::setDistanceToMove(float dist)
{
    toMove = dist;
}

bool Elodie::isMoving()
{
    return goingDown or goingLeft or goingRight or goingUp;
}

bool Elodie::hasToMove()
{
    return toMove > 0;
}

void Elodie::noMoves()
{
    toMove = 0;
    goingDown = false;
    goingLeft = false;
    goingRight = false;
    goingUp = false;
}

void Elodie::update(sf::Time deltaTime)
{
    this->sprite->update(deltaTime);
}

int Elodie::getImmersionLevel() {
    return this->immersionLevel;
}

int Elodie::getNightmareLevel() {
    return this->nightmareLevel;
}



void Elodie::init()
{
    this->sprite = new ElodieSprite();
}

void Elodie::walk()
{
    this->sprite->walk();
}
