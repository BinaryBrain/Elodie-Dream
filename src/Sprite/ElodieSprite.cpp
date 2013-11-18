#include "ElodieSprite.h"

ElodieSprite::ElodieSprite() : CharacterSprite() {
    texture.loadFromFile("assets/img/sprite.png");

    // push frames
    walkingAnimation.setSpriteSheet(texture);

    walkingAnimation.addFrame(sf::IntRect(85, 0, 48, 64));
    walkingAnimation.addFrame(sf::IntRect(85+50, 0, 46, 64));
    walkingAnimation.addFrame(sf::IntRect(85+100, 0, 46, 64));
    walkingAnimation.addFrame(sf::IntRect(85+157, 0, 46, 64));
    walkingAnimation.addFrame(sf::IntRect(85+202, 0, 46, 64));
    walkingAnimation.addFrame(sf::IntRect(85+246, 0, 46, 64));
    walkingAnimation.addFrame(sf::IntRect(85+290, 0, 46, 64));

    standingAnimation.setSpriteSheet(texture);
    standingAnimation.addFrame(sf::IntRect(0, 0, 43, 64));

    setAnimation(standingAnimation);
}

ElodieSprite::~ElodieSprite() {
    //dtor
}

void ElodieSprite::walk() {
    AnimatedSprite::setAnimation(walkingAnimation);
}

void ElodieSprite::stand() {
    AnimatedSprite::setAnimation(standingAnimation);
}
