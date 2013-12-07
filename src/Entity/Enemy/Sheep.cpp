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

    EntityManager* ToyBox = EntityManager::getInstance();
    EntityInfo* sheepInfo = ToyBox->getEnemyInfo(EntityType::ENEMY, EntityName::SHEEP);

    x -= sheepInfo->width;
    y -= sheepInfo->height / 2 - 1;
    state = SheepState::STANDING;
    speed.x = 0;

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

void Sheep::doStuff(EventHandler* const& event, std::vector< std::vector<TileSprite*> > const& tiles, sf::Time animate) {
    Collide collideTiles = collideWithTiles(tiles, &speed, animate.asSeconds(), getCurrentHitbox(ANIMATIONS[state], sprite->getCurrentFrame()));

    move(animate.asSeconds()*speed.x, animate.asSeconds()*speed.y);

    sprite->update(animate);
}

void Sheep::pause() {
    sprite->pause();
}

void Sheep::play() {
    sprite->play();
}
