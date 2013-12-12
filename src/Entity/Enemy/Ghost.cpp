#include "Ghost.h"

Ghost::Ghost() {
    init(0, 0);
}

Ghost::Ghost(sf::Vector2f position) {
    init(position.x, position.y);
}

Ghost::Ghost(float x, float y) {
    init(x, y);
}

void Ghost::init(float x, float y) {
    ANIMATIONS = {
        {GhostState::STANDING, "standing"}
    };

    damage = GHOST_DAMAGE;
    life = 1;

    EntityManager* ToyBox = EntityManager::getInstance();
    info = ToyBox->getEnemyInfo(EntityType::ENEMY, EntityName::GHOST);

    x -= info->width / 2;
    y -= (info->height - BLOCK_SIZE);
    state = GhostState::STANDING;

    sprite = new EntitySprite(info, ENTITIES_JSON_PATH+"/"+ENTITYTYPE_ENEMY+"/"+ENTITYNAME_GHOST+".png", "standing");
    setEntitySprite(sprite);

    sprite->setPosition(sf::Vector2f(x,y));
    setHitboxes(info, sprite->getPosition());
    soundManager = SoundManager::getInstance();
}

Ghost::~Ghost() {
    delete sprite;
    sprite = NULL;
    setEntitySprite(NULL);
}

void Ghost::update(sf::Time deltaTime) {
    sprite->update(deltaTime);
}

EntitySprite* Ghost::getSprite() {
    return sprite;
}

void Ghost::doAttack(std::map< std::string, Entity* >& entities) {
    sf::FloatRect entity = getCurrentHitbox(ANIMATIONS[state], sprite->getCurrentFrame()).getArea();
    Elodie* elodie = (Elodie*) entities["elodie"];
    if (entity.intersects(elodie->returnCurrentHitbox().getArea()))
        elodie->takeDamage(damage, false);
}

Hitbox Ghost::returnCurrentHitbox() {
    return getCurrentHitbox(ANIMATIONS[state], sprite->getCurrentFrame());
}

void  Ghost::takeDamage(int damage, bool ignore) {
    if (!damageCD && damage > 0) {
        life = 0;
        damageCD = DAMAGE_CD;
        soundManager->play(SoundType::GHOST);
    }
}

void Ghost::doStuff(EventHandler* const& event, std::vector< std::vector<TileSprite*> > const& tiles, std::map< std::string, Entity* >& entities, sf::Time animate) {
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

void Ghost::pause() {
    sprite->pause();
}

void Ghost::play() {
    sprite->play();
}
