#include "../Score/ScoreManager.h"
#include "../Sound/SoundManager.h"
#include "Bonus.h"

const int Bonus::POINTS = 50;

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

    info = EntityManager::getInstance().getEnemyInfo(EntityType::BONUS, EntityName::SPRITE);

    y -= (info->height - BLOCK_SIZE);
    state = BonusState::STANDING;

    sprite = new EntitySprite(info, ENTITIES_JSON_PATH+"/"+ENTITYTYPE_BONUS+"/"+ENTITYNAME_SPRITE+".png", "standing");
    setEntitySprite(sprite);

    sprite->changeStance(ANIMATIONS[state], sf::seconds(0.2f));

    sprite->setPosition(sf::Vector2f(x,y));
    setHitboxes(info, sprite->getPosition());
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

void Bonus::takeDamage(int, bool) {
    // nothing here lol
}

void Bonus::getTaken(std::map< std::string, Entity* >& entities) {
    sf::FloatRect zone = getCurrentHitbox(ANIMATIONS[state], sprite->getCurrentFrame()).getArea();
    sf::FloatRect elodie = ((Elodie*)entities["elodie"])->returnCurrentHitbox().getArea();
    if (zone.intersects(elodie)) {
        ScoreManager& sm = ScoreManager::getInstance();
        sm.takeBonus();
        sm.addToLevelPoints(POINTS);
        life = 0;
	SoundManager::getInstance().play(SoundType::BOTTLE);
    }
}

void Bonus::doStuff(EventHandler* const&, std::vector< std::vector<TileSprite*> > const&, std::map< std::string, Entity* >& entities, sf::Time animate) {
    getTaken(entities);
    sprite->update(animate);
}

void Bonus::pause() {
    sprite->pause();
}

void Bonus::play() {
    sprite->play();
}
