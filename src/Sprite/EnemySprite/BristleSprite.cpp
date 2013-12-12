#include "BristleSprite.h"

BristleSprite::BristleSprite(EntityInfo *informations) : EnemySprite() {
    texture.loadFromFile(ENTITIES_JSON_PATH+"/"+ENTITYTYPE_ENEMY+"/"+ENTITYNAME_BRISTLE+".png");

    // push frames
    for(std::map< std::string, HitboxInfo >::iterator it = informations->anim.begin(); it != informations->anim.end(); ++it) {
        animations[it->first].setSpriteSheet(texture);
        for(int i(0); i < 4; ++i) {
            animations[it->first].addFrame(sf::IntRect(i * informations->width, it->second.row * informations->height, informations->width, informations->height));
        }
    }

    changeStance("standing", sf::seconds(0.1));
}

BristleSprite::~BristleSprite() {
    //dtor
}

void BristleSprite::changeStance(std::string stance, sf::Time speed) {
    AnimatedSprite::setAnimation(animations[stance]);
    setFrameTime(speed);
    setCurrentStance(stance);
}
