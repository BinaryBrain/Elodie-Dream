#include "Bonus.h"

Bonus::Bonus() {
    init(0, 0);
}

Bonus::Bonus(sf::Vector2f position) {
    init(position.x, position.y);
}

Bonus::Bonus(float x, float y) {
    init(x, y);
}

void Bonus::init(float x, float y) {
    ANIMATIONS = {
        {BonusState::STANDING, "standing"}
    };

    damage = 0;
    life = 1;

    EntityManager* ToyBox = EntityManager::getInstance();
    info = ToyBox->getEnemyInfo(EntityType::BONUS, EntityName::SPRITE);

    y -= (info->height - BLOCK_SIZE);
    state = BonusState::STANDING;

    sprite = new EntitySprite(info, ENTITIES_JSON_PATH+"/"+ENTITYTYPE_BONUS+"/"+ENTITYNAME_SPRITE+".png", "standing");
    setEntitySprite(sprite);


    sprite->setPosition(sf::Vector2f(x,y));
    setHitboxes(info, sprite->getPosition());
    soundManager = SoundManager::getInstance();
}

Bonus::~Bonus() {
    delete sprite;
    sprite = NULL;
    setEntitySprite(NULL);
}

void Bonus::update(sf::Time deltaTime) {
    sprite->update(deltaTime);
}

EntitySprite* Bonus::getSprite() {
    return sprite;
}

Hitbox Bonus::returnCurrentHitbox() {
    return getCurrentHitbox(ANIMATIONS[state], sprite->getCurrentFrame());
}

void  Bonus::takeDamage(int damage, bool ignore) {
    // nothing here lol
}

void Bonus::doStuff(EventHandler* const& event, std::vector< std::vector<TileSprite*> > const& tiles, std::map< std::string, Entity* >& entities, sf::Time animate) {
    sprite->update(animate);
}

void Bonus::pause() {
    sprite->pause();
}

void Bonus::play() {
    sprite->play();
}
