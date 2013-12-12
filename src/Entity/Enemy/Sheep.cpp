#include "Sheep.h"

Sheep::Sheep() {
    init(0, 0);
}

Sheep::Sheep(sf::Vector2f position) {
    init(position.x, position.y);
}

Sheep::Sheep(float x, float y) {
    init(x, y);
}

void Sheep::init(float x, float y) {
    ANIMATIONS = {
        {SheepState::STANDING, "standing"}
    };

    damage = SHEEP_DAMAGE;
    life = 1;

    EntityManager* ToyBox = EntityManager::getInstance();
    EntityInfo* sheepInfo = ToyBox->getEnemyInfo(EntityType::ENEMY, EntityName::SHEEP);

    x -= sheepInfo->width / 2;
    y -= (sheepInfo->height - BLOCK_SIZE);
    state = SheepState::STANDING;

    sprite = new SheepSprite(sheepInfo);
    setEntitySprite(sprite);

    sprite->setPosition(sf::Vector2f(x,y));
    setHitboxes(sheepInfo, sprite->getPosition());
}

Sheep::~Sheep() {
    delete sprite;
    sprite = NULL;
    setEntitySprite(NULL);
}

void Sheep::update(sf::Time deltaTime) {
    sprite->update(deltaTime);
}

SheepSprite* Sheep::getSprite() {
    return sprite;
}

void Sheep::doAttack(std::map< std::string, Entity* >& entities) {
    sf::FloatRect entity = getCurrentHitbox(ANIMATIONS[state], sprite->getCurrentFrame()).getArea();
    Elodie* elodie = (Elodie*) entities["elodie"];
    if (entity.intersects(elodie->returnCurrentHitbox().getArea()))
        elodie->takeDamage(damage, false);
}

Hitbox Sheep::returnCurrentHitbox() {
    return getCurrentHitbox(ANIMATIONS[state], sprite->getCurrentFrame());
}

void  Sheep::takeDamage(int damage, bool ignore) {
    if (!damageCD && damage > 0) {
        life = 0;
        damageCD = DAMAGE_CD;
        std::cout << "BEEEEEEEEEEEEEEEEEEEEEH" << std::endl;
    }
}

void Sheep::doStuff(EventHandler* const& event, std::vector< std::vector<TileSprite*> > const& tiles, std::map< std::string, Entity* >& entities, sf::Time animate) {
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

void Sheep::pause() {
    sprite->pause();
}

void Sheep::play() {
    sprite->play();
}
