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
    speed.x = -GHOST_SPEED_X;

    info = EntityManager::getInstance().getEnemyInfo(EntityType::ENEMY, EntityName::GHOST);

    y -= (info->height - BLOCK_SIZE);
    state = GhostState::STANDING;

    sprite = new EntitySprite(info, ENTITIES_JSON_PATH+"/"+ENTITYTYPE_ENEMY+"/"+ENTITYNAME_GHOST+".png", "standing");
    setEntitySprite(sprite);

    sprite->setPosition(sf::Vector2f(x,y));
    setHitboxes(info, sprite->getPosition());
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

void  Ghost::takeDamage(int, bool) {
    //GHOSTS ARE IMMORTAL BITCHES
}

void Ghost::doStuff(EventHandler* const&, std::vector< std::vector<TileSprite*> > const&, std::map< std::string, Entity* >& entities, sf::Time animate) {
    move(animate.asSeconds()*(speed.x), animate.asSeconds()*speed.y);
    sprite->update(animate);

    if (speed.y < 0 && speed.y < -limitSpeed) {
        step = GHOST_STEP;
    } else if (speed.y > 0 && speed.y > limitSpeed) {
        step = -GHOST_STEP;
    }
    speed.y += step;

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
