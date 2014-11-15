#include "ElodieSprite.h"

ElodieSprite::ElodieSprite(EntityInfo *informations) : CharacterSprite()
{
    texture.loadFromFile(ENTITIES_JSON_PATH+"/"+ENTITYNAME_ELODIE+".png");

    // push frames
    for(std::map< std::string, HitboxInfo >::iterator it = informations->anim.begin(); it != informations->anim.end(); ++it)
    {
        animations[it->first].setSpriteSheet(texture);
        for(int i(0); i < 4; ++i)
        {
            animations[it->first].addFrame(sf::IntRect(i * informations->width, it->second.row * informations->height, informations->width, informations->height));
        }
    }

    stand();
}

ElodieSprite::~ElodieSprite()
{
    //dtor
}

void ElodieSprite::changeStance(std::string stance, sf::Time speed)
{
    AnimatedSprite::setAnimation(animations[stance]);
    setFrameTime(speed);
    setCurrentStance(stance);
}

void ElodieSprite::walk()
{
    AnimatedSprite::setAnimation(animations["running"]);
    setFrameTime(sf::seconds(0.1));
    setCurrentStance("running");
}

void ElodieSprite::stand()
{
    AnimatedSprite::setAnimation(animations["standing"]);
    AnimatedSprite::setFrameTime(sf::seconds(0.2));
    setCurrentStance("standing");
}
