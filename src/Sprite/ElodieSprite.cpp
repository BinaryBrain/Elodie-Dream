#include "ElodieSprite.h"

ElodieSprite::ElodieSprite() : CharacterSprite() {
    texture.loadFromFile("assets/img/sprites/elodie_d.png");

    // push frames
    walkingAnimationRight.setSpriteSheet(texture);

    walkingAnimationRight.addFrame(sf::IntRect(0, 64, 63, 63));
    walkingAnimationRight.addFrame(sf::IntRect(64, 64, 63, 63));
    walkingAnimationRight.addFrame(sf::IntRect(128, 64, 63, 63));
    walkingAnimationRight.addFrame(sf::IntRect(192, 64, 63, 63));

    standingAnimation.setSpriteSheet(texture);
    standingAnimation.addFrame(sf::IntRect(0, 0, 63, 63));
    standingAnimation.addFrame(sf::IntRect(64, 0, 63, 63));
    standingAnimation.addFrame(sf::IntRect(128, 0, 63, 63));
    standingAnimation.addFrame(sf::IntRect(192, 0, 63, 63));


    stand();
}

ElodieSprite::~ElodieSprite() {
    //dtor
}

void ElodieSprite::walk() {
    AnimatedSprite::setAnimation(walkingAnimationRight);
    setFrameTime(sf::seconds(0.1));
    setCurrentStance(SpriteStance::WALKING_RIGHT);
}

void ElodieSprite::stand() {
    AnimatedSprite::setAnimation(standingAnimation);
    AnimatedSprite::setFrameTime(sf::seconds(0.2));
    setCurrentStance(SpriteStance::STANDING);
}
