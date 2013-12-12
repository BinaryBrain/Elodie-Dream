#ifndef PORTALSPRITE_H
#define PORTALSPRITE_H

#include "../env.h"
#include "AnimatedSprite.h"

class PortalSprite: public AnimatedSprite {
public:
    PortalSprite(EntityInfo *informations);
    virtual ~PortalSprite();
protected:
private:
    std::map< std::string, Animation > animations;
    sf::Texture texture;
};

#endif // PORTALSPRITE_H
