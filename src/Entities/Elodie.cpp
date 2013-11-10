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

sf::Vector2f* Elodie::getPosition()
{
    return new sf::Vector2f(this->sprite->getPosition().x+centerX,this->sprite->getPosition().y+centerY);
}

void Elodie::walk()
{
    this->sprite->walk();
}

void Elodie::stand()
{
    this->sprite->stand();
}

void Elodie::init()
{
    this->sprite = new ElodieSprite();
}

Elodie::~Elodie()
{
    //  TODO : maybe source of memory leak
    //  delete this->sprite;
}
