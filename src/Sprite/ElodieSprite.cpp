#include "ElodieSprite.h"

ElodieSprite::ElodieSprite() : CharacterSprite()
{
    this->texture.loadFromFile("assets/img/sprite.png");

    // push frames
    this->walkingAnimation.setSpriteSheet(this->texture);

    this->walkingAnimation.addFrame(sf::IntRect(85, 0, 48, 64));
    this->walkingAnimation.addFrame(sf::IntRect(85+50, 0, 46, 64));
    this->walkingAnimation.addFrame(sf::IntRect(85+100, 0, 46, 64));
    this->walkingAnimation.addFrame(sf::IntRect(85+157, 0, 46, 64));
    this->walkingAnimation.addFrame(sf::IntRect(85+202, 0, 46, 64));
    this->walkingAnimation.addFrame(sf::IntRect(85+246, 0, 46, 64));
    this->walkingAnimation.addFrame(sf::IntRect(85+290, 0, 46, 64));

    this->standingAnimation.setSpriteSheet(this->texture);
    this->standingAnimation.addFrame(sf::IntRect(0, 0, 43, 64));
}

ElodieSprite::~ElodieSprite()
{
    //dtor
}

void ElodieSprite::walk(){
    AnimatedSprite::setAnimation(this->walkingAnimation);
}

void ElodieSprite::stand(){
    AnimatedSprite::setAnimation(this->standingAnimation);
}
