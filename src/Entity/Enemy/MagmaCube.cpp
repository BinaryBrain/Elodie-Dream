#include "MagmaCube.h"

MagmaCube::MagmaCube() {
    init(0, 0);
}

MagmaCube::MagmaCube(sf::Vector2f position) {
    init(position.x, position.y);
}

MagmaCube::MagmaCube(float x, float y) {
    init(x, y);
}

void MagmaCube::init(float x, float y) {
    ANIMATIONS = {
        {MagmaCubeState::STANDING, "standing"}
    };

    damage = MAGMACUBE_DAMAGE;

    EntityManager* ToyBox = EntityManager::getInstance();
    EntityInfo* magmaCubeInfo = ToyBox->getEnemyInfo(EntityType::ENEMY, EntityName::MAGMACUBE);

    x -= magmaCubeInfo->width / 2;
    y -= (magmaCubeInfo->height - BLOCK_SIZE);
    state = MagmaCubeState::STANDING;
    speed.x = 0;

    sprite = new MagmaCubeSprite(magmaCubeInfo);
    setEntitySprite(sprite);

    sprite->setPosition(sf::Vector2f(x,y));
    setHitboxes(magmaCubeInfo, sprite->getPosition());
}

MagmaCube::~MagmaCube() {
    delete sprite;
    sprite = NULL;
    setEntitySprite(NULL);
}

void MagmaCube::update(sf::Time deltaTime) {
    sprite->update(deltaTime);
}

MagmaCubeSprite* MagmaCube::getSprite() {
    return sprite;
}

void MagmaCube::doAttack(std::map< std::string, Entity* >& entities) {
    sf::FloatRect entity = getCurrentHitbox(ANIMATIONS[state], sprite->getCurrentFrame()).getArea();
    Elodie* elodie = (Elodie*) entities["elodie"];
    if (entity.intersects(elodie->returnCurrentHitbox().getArea()))
        elodie->takeDamage(damage);
}

Hitbox MagmaCube::returnCurrentHitbox() {
    return getCurrentHitbox(ANIMATIONS[state], sprite->getCurrentFrame());
}

void MagmaCube::doStuff(EventHandler* const& event, std::vector< std::vector<TileSprite*> > const& tiles, std::map< std::string, Entity* >& entities, sf::Time animate) {
    Collide collideTiles = collideWithTiles(tiles, &speed, animate.asSeconds(), getCurrentHitbox(ANIMATIONS[state], sprite->getCurrentFrame()));

    doAttack(entities);

    move(animate.asSeconds()*speed.x, animate.asSeconds()*speed.y);

    sprite->update(animate);
}

void MagmaCube::pause() {
    sprite->pause();
}

void MagmaCube::play() {
    sprite->play();
}
