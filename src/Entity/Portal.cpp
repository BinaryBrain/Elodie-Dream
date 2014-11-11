#include "Portal.h"

Portal::Portal() {
    init(0, 0);
}

Portal::Portal(sf::Vector2f position) {
    init(position.x, position.y);
}

Portal::Portal(float x, float y) {
    init(x, y);
}

void Portal::init(float x, float y) {
    ANIMATIONS = {
        {PortalState::STANDING, "standing"}
    };

    damage = 0;
    life = 1;

    info = EntityManager::getInstance().getEnemyInfo(EntityType::MISC, EntityName::PORTAL);

    y -= (info->height - BLOCK_SIZE);
    state = PortalState::STANDING;

    sprite = new EntitySprite(info, ENTITIES_JSON_PATH+"/"+ENTITYTYPE_MISC+"/"+ENTITYNAME_PORTAL+".png", "standing");
    setEntitySprite(sprite);


    sprite->setPosition(sf::Vector2f(x,y));
    setHitboxes(info, sprite->getPosition());
}

Portal::~Portal() {
    delete sprite;
    sprite = NULL;
    setEntitySprite(NULL);
}

void Portal::update(sf::Time deltaTime) {
    sprite->update(deltaTime);
}

EntitySprite* Portal::getSprite() {
    return sprite;
}

Hitbox Portal::returnCurrentHitbox() {
    return getCurrentHitbox(ANIMATIONS[state], sprite->getCurrentFrame());
}

void  Portal::takeDamage(int, bool) {
    // nothing here lol
}

void Portal::doStuff(EventHandler* const&, std::vector< std::vector<TileSprite*> > const&, std::map< std::string, Entity* >&, sf::Time animate) {
    sprite->update(animate);
}

void Portal::pause() {
    sprite->pause();
}

void Portal::play() {
    sprite->play();
}
