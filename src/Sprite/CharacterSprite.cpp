#include "CharacterSprite.h"
//Default value 0.1, could be changed !
CharacterSprite::CharacterSprite() : AnimatedSprite(sf::seconds(0.1))
{
    //ctor
}

CharacterSprite::~CharacterSprite()
{
    //dtor
}

std::string CharacterSprite::getCurrentStance()
{
    return currentStance;
}

void CharacterSprite::setCurrentStance(std::string newStance)
{
    currentStance = newStance;
}
