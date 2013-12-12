#include "Bristle.h"

Bristle::Bristle() {
    init(0, 0);
}

Bristle::Bristle(sf::Vector2f position) {
    init(position.x, position.y);
}

Bristle::Bristle(float x, float y) {
    init(x, y);
}

void Bristle::init(float x, float y) {
    ANIMATIONS = {
        {BristleState::STANDING, "standing"}
    };

    damage = BRISTLE_DAMAGE;
    life = 1;

    EntityManager* ToyBox = EntityManager::getInstance();
    info = ToyBox->getEnemyInfo(EntityType::ENEMY, EntityName::BRISTLE);

    y -= (info->height - BLOCK_SIZE);
    state = BristleState::STANDING;

    sprite = new EntitySprite(info, ENTITIES_JSON_PATH+"/"+ENTITYTYPE_ENEMY+"/"+ENTITYNAME_BRISTLE+".png", "standing");
    setEntitySprite(sprite);

    sprite->setPosition(sf::Vector2f(x,y));
    setHitboxes(info, sprite->getPosition());
    soundManager = SoundManager::getInstance();
}

Bristle::~Bristle() {
    delete sprite;
    sprite = NULL;
    setEntitySprite(NULL);
}

void Bristle::update(sf::Time deltaTime) {
    sprite->update(deltaTime);
}

EntitySprite* Bristle::getSprite() {
    return sprite;
}

void Bristle::doAttack(std::map< std::string, Entity* >& entities) {
    sf::FloatRect entity = getCurrentHitbox(ANIMATIONS[state], sprite->getCurrentFrame()).getArea();
    Elodie* elodie = (Elodie*) entities["elodie"];
    if (entity.intersects(elodie->returnCurrentHitbox().getArea()))
        elodie->takeDamage(damage, false);
}

Hitbox Bristle::returnCurrentHitbox() {
    return getCurrentHitbox(ANIMATIONS[state], sprite->getCurrentFrame());
}

void  Bristle::takeDamage(int damage, bool ignore) {
    if (!damageCD && damage > 0) {
        life = 0;
        damageCD = DAMAGE_CD;
    }
}

void Bristle::doStuff(EventHandler* const& event, std::vector< std::vector<TileSprite*> > const& tiles, std::map< std::string, Entity* >& entities, sf::Time animate) {
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

void Bristle::pause() {
    sprite->pause();
}

void Bristle::play() {
    sprite->play();
}
