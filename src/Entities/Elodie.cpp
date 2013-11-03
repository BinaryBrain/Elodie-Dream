#include "Elodie.h"

Elodie::Elodie() {
    this->init();
}

Elodie::Elodie(sf::Vector2f position) {
    this->init();
    this->sprite->setPosition(position);
}

void Elodie::init() {
    this->sprite = new ElodieSprite();
}

Elodie::~Elodie()
{
    delete this->sprite;
}
