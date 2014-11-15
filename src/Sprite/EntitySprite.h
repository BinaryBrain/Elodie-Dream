#ifndef ENTITYSPRITE_H
#define ENTITYSPRITE_H

#include "CharacterSprite.h"

#include <iostream>
#include <string>
#include <map>

#include "../const.h"
#include "../env.h"
#include "../Include/EntityInfo.h"


class EntitySprite : public CharacterSprite
{
public:
    EntitySprite(EntityInfo *informations, std::string path, std::string stance);
    virtual ~EntitySprite();
    void changeStance(const std::string& stance, const sf::Time& speed);
protected:
private:
    std::map< std::string, Animation > animations;
    sf::Texture texture;
};

#endif // ENTITYSPRITE_H
