#ifndef PORTALSPRITE_H
#define PORTALSPRITE_H

#include <iostream>
#include <string>
#include <map>

#include "../const.h"
#include "../env.h"
#include "EnemySprite.h"
#include "../Include/EntityInfo.h"

class PortalSprite: public EnemySprite {
public:
    PortalSprite(EntityInfo *informations);
    virtual ~PortalSprite();
    void changeStance(std::string stance, sf::Time speed);
protected:
private:
    std::map< std::string, Animation > animations;
    sf::Texture texture;
};

#endif // PORTALSPRITE_H
