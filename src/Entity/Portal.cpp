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

    EntityManager* ToyBox = EntityManager::getInstance();
    info = ToyBox->getEnemyInfo(EntityType::MISC, EntityName::PORTAL);

    x -= info->width / 2;
    y -= (info->height - BLOCK_SIZE);
    state = PortalState::STANDING;

    sprite = new PortalSprite(info);
    setEntitySprite(sprite);

    sprite->setPosition(sf::Vector2f(x,y));
    setHitboxes(info, sprite->getPosition());
    soundManager = SoundManager::getInstance();
}

Portal::~Portal() {
    delete sprite;
    sprite = NULL;
    setEntitySprite(NULL);
}

void Portal::update(sf::Time deltaTime) {
    sprite->update(deltaTime);
}

PortalSprite* Portal::getSprite() {
    return sprite;
}

Hitbox Portal::returnCurrentHitbox() {
    return getCurrentHitbox(ANIMATIONS[state], sprite->getCurrentFrame());
}


void Portal::doStuff(EventHandler* const& event, std::vector< std::vector<TileSprite*> > const& tiles, std::map< std::string, Entity* >& entities, sf::Time animate) {
    //Compute the gravity
    computeGravity(animate);

    //Check the collisions, set the new distances and do the move
    Collide collideTiles = collideWithTiles(tiles, &speed, animate.asSeconds(), getCurrentHitbox(ANIMATIONS[state], sprite->getCurrentFrame()));
    setDistance(collideTiles);
    move(animate.asSeconds()*(speed.x), animate.asSeconds()*speed.y);
    sprite->update(animate);
}

void Portal::pause() {
    sprite->pause();
}

void Portal::play() {
    sprite->play();
}
