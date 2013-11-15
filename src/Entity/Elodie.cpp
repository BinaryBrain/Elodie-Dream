#include "Elodie.h"

Elodie::Elodie()
{
    this->init();
}

Elodie::Elodie(sf::Vector2f position)
{
    this->init();
    this->m_sprite->setPosition(position.x - m_centerX, position.y - m_centerY);
}

Elodie::Elodie(float x, float y)
{
    this->init();
    this->m_sprite->setPosition(x - m_centerX, y - m_centerY);
}

ElodieSprite* Elodie::getSprite()
{
    return this->m_sprite;
}

Elodie::~Elodie()
{
    //  TODO : maybe source of memory leak
    //  delete this->sprite;
}

sf::Vector2f* Elodie::getPosition()
{
    return new sf::Vector2f(this->m_sprite->getPosition().x + m_centerX, this->m_sprite->getPosition().y + m_centerY);
}

void Elodie::stand()
{
    this->m_sprite->stand();
}

void Elodie::move()
{
    if (m_goingDown)
    {
        m_toMove -= m_speed;
        this->m_sprite->move(0, m_speed);
    }
    else if (m_goingLeft)
    {
        m_toMove -= m_speed;
        this->m_sprite->move(-m_speed, 0);
    }
    else if (m_goingRight)
    {
        m_toMove -= m_speed;
        this->m_sprite->move(+m_speed, 0);
    }
    else if (m_goingUp)
    {
        m_toMove -= m_speed;
        this->m_sprite->move(0, -m_speed);
    }
    else
    {
        noMoves();
    }
}

void Elodie::walkDown()
{
    this->walk();
    m_goingDown = true;
}
void Elodie::walkUp()
{
    this->walk();
    m_goingUp = true;
}
void Elodie::walkRight()
{
    this->walk();
    m_goingRight = true;
}
void Elodie::walkLeft()
{
    this->walk();
    m_goingLeft = true;
}

void Elodie::setDistanceToMove(float dist)
{
    m_toMove = dist;
}

bool Elodie::isMoving()
{
    return m_goingDown or m_goingLeft or m_goingRight or m_goingUp;
}

bool Elodie::hasToMove()
{
    return m_toMove > 0;
}

void Elodie::noMoves()
{
    m_toMove = 0;
    m_goingDown = false;
    m_goingLeft = false;
    m_goingRight = false;
    m_goingUp = false;
}

void Elodie::update(sf::Time deltaTime)
{
    this->m_sprite->update(deltaTime);
}

int Elodie::getImmersionLevel() {
    return this->m_immersionLevel;
}

int Elodie::getNightmareLevel() {
    return this->m_nightmareLevel;
}



void Elodie::init()
{
    this->m_sprite = new ElodieSprite();
}

void Elodie::walk()
{
    this->m_sprite->walk();
}
