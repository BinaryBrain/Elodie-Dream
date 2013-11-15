#include "Elodie.h"

Elodie::Elodie() {
    init();
}

Elodie::Elodie(sf::Vector2f position) {
    init();
    sprite->setPosition(position.x - centerX, position.y - centerY);
}

Elodie::Elodie(float x, float y) {
    init();
    sprite->setPosition(x - centerX, y - centerY);
}

ElodieSprite* Elodie::getSprite() {
    return sprite;
}

Elodie::~Elodie() {
    //  TODO : maybe source of memory leak
    //  delete sprite;
}

sf::Vector2f* Elodie::getPosition() {
    return new sf::Vector2f(sprite->getPosition().x + centerX, sprite->getPosition().y + centerY);
}

void Elodie::stand() {
    sprite->stand();
}

void Elodie::move() {
    if (goingDown) {
        toMove -= speed;
        sprite->move(0, speed);
    } else if (goingLeft) {
        toMove -= speed;
        sprite->move(-speed, 0);
    } else if (goingRight) {
        toMove -= speed;
        sprite->move(+speed, 0);
    } else if (goingUp) {
        toMove -= speed;
        sprite->move(0, -speed);
    } else {
        noMoves();
    }
}

void Elodie::walkDown() {
    this->walk();
    goingDown = true;
}
void Elodie::walkUp() {
    this->walk();
    goingUp = true;
}
void Elodie::walkRight() {
    this->walk();
    goingRight = true;
}
void Elodie::walkLeft() {
    this->walk();
    goingLeft = true;
}

void Elodie::setDistanceToMove(float dist) {
    toMove = dist;
}

bool Elodie::isMoving() {
    return goingDown or goingLeft or goingRight or goingUp;
}

bool Elodie::hasToMove() {
    return toMove > 0;
}

void Elodie::noMoves() {
    toMove = 0;
    goingDown = false;
    goingLeft = false;
    goingRight = false;
    goingUp = false;
}

void Elodie::update(sf::Time deltaTime) {
    sprite->update(deltaTime);
}

int Elodie::getImmersionLevel() {
    return immersionLevel;
}

int Elodie::getNightmareLevel() {
    return nightmareLevel;
}



void Elodie::init() {
    sprite = new ElodieSprite();
}

void Elodie::walk() {
    sprite->walk();
}
