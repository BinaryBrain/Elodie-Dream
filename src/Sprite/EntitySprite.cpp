#include "EntitySprite.h"

EntitySprite::EntitySprite(EntityInfo *informations, std::string path, std::string stance) : CharacterSprite()
{
    texture.loadFromFile(path);

    // push frames
    for(std::map< std::string, HitboxInfo >::iterator it = informations->anim.begin(); it != informations->anim.end(); ++it)
    {
        animations[it->first].setSpriteSheet(texture);
        for(int i(0); i < 4; ++i)
        {
            animations[it->first].addFrame(sf::IntRect(i * informations->width, it->second.row * informations->height, informations->width, informations->height));
        }
    }

    changeStance(stance, sf::seconds(0.1));
}

EntitySprite::~EntitySprite()
{
    //dtor
}

void EntitySprite::changeStance(const std::string& stance, const sf::Time& speed)
{
    AnimatedSprite::setAnimation(animations[stance]);
    setFrameTime(speed);
    setCurrentStance(stance);
}
