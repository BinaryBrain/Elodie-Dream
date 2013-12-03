#include "ElodieSprite.h"

ElodieSprite::ElodieSprite() : CharacterSprite() {
    texture.loadFromFile("assets/img/sprites/elodie_d.png");

    // push frames
    walkingAnimationRight.setSpriteSheet(texture);

    walkingAnimationRight.addFrame(sf::IntRect(85, 0, 48, 64));
    walkingAnimationRight.addFrame(sf::IntRect(85+50, 0, 46, 64));
    walkingAnimationRight.addFrame(sf::IntRect(85+100, 0, 46, 64));
    walkingAnimationRight.addFrame(sf::IntRect(85+157, 0, 46, 64));
    walkingAnimationRight.addFrame(sf::IntRect(85+202, 0, 46, 64));
    walkingAnimationRight.addFrame(sf::IntRect(85+246, 0, 46, 64));
    walkingAnimationRight.addFrame(sf::IntRect(85+290, 0, 46, 64));

    standingAnimation.setSpriteSheet(texture);
    standingAnimation.addFrame(sf::IntRect(0, 0, 43, 64));

    setAnimation(standingAnimation);
    setCurrentStance(SpriteStance::STANDING);
}

ElodieSprite::~ElodieSprite() {
    //dtor
}

void ElodieSprite::walk() {
    AnimatedSprite::setAnimation(walkingAnimationRight);
    setCurrentStance(SpriteStance::WALKING_RIGHT);
}

void ElodieSprite::stand() {
    AnimatedSprite::setAnimation(standingAnimation);
    setCurrentStance(SpriteStance::STANDING);
}
