#include "PortalSprite.h"

PortalSprite::PortalSprite(EntityInfo *informations) : AnimatedSprite() {
    texture.loadFromFile(ENTITIES_JSON_PATH+"/"+ENTITYTYPE_MISC+"/"+ENTITYNAME_PORTAL+".png");

    // push frames
    for(std::map< std::string, HitboxInfo >::iterator it = informations->anim.begin(); it != informations->anim.end(); ++it) {
        animations[it->first].setSpriteSheet(texture);
        for(int i(0); i < 4; ++i) {
            animations[it->first].addFrame(sf::IntRect(i * informations->width, it->second.row * informations->height, informations->width, informations->height));
        }
    }
}

PortalSprite::~PortalSprite() {
    //dtor
}
