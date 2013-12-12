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

    EntityManager* ToyBox = EntityManager::getInstance();
    info = ToyBox->getEnemyInfo(EntityType::MISC, EntityName::PORTAL);

    x -= info->width / 2;
    y -= (info->height - BLOCK_SIZE);
    state = PortalState::STANDING;

    std::cout << "Before creating portal sprite" << std::endl;
    sprite = new PortalSprite(info);
    std::cout << "Created portal sprite" << std::endl;
    setEntitySprite(sprite);
    std::cout << "Set entity sprite done" << std::endl;

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

void Portal::doAttack(std::map< std::string, Entity* >& entities) {
    sf::FloatRect entity = getCurrentHitbox(ANIMATIONS[state], sprite->getCurrentFrame()).getArea();
    Elodie* elodie = (Elodie*) entities["elodie"];
    if (entity.intersects(elodie->returnCurrentHitbox().getArea()))
        elodie->takeDamage(damage, false);
}

Hitbox Portal::returnCurrentHitbox() {
    return getCurrentHitbox(ANIMATIONS[state], sprite->getCurrentFrame());
}

void  Portal::takeDamage(int damage, bool ignore) {
    if (!damageCD && damage > 0) {
        life = 0;
        damageCD = DAMAGE_CD;
        soundManager->play(SoundType::SHEEP);
    }
}

void Portal::doStuff(EventHandler* const& event, std::vector< std::vector<TileSprite*> > const& tiles, std::map< std::string, Entity* >& entities, sf::Time animate) {
    //Compute the gravity
    computeGravity(animate);

    //Check the collisions, set the new distances and do the move
    Collide collideTiles = collideWithTiles(tiles, &speed, animate.asSeconds(), getCurrentHitbox(ANIMATIONS[state], sprite->getCurrentFrame()));
    setDistance(collideTiles);
    move(animate.asSeconds()*(speed.x), animate.asSeconds()*speed.y);
    sprite->update(animate);

    doAttack(entities);

    if (damageCD)
        --damageCD;
}

void Portal::pause() {
    sprite->pause();
}

void Portal::play() {
    sprite->play();
}
