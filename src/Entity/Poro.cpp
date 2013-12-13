#include "Poro.h"

Poro::Poro() {
    init(0, 0);
}

Poro::Poro(sf::Vector2f position) {
    init(position.x, position.y);
}

Poro::Poro(float x, float y) {
    init(x, y);
}

void Poro::init(float x, float y) {
    ANIMATIONS = {
        {PoroState::RUNNING, "running"}
    };

    damage = 0;
    life = 1;

    EntityManager* ToyBox = EntityManager::getInstance();
    info = ToyBox->getEnemyInfo(EntityType::ELODIE, EntityName::PORO);

    y -= (info->height - BLOCK_SIZE);
    state = PoroState::RUNNING;

    sprite = new EntitySprite(info, ENTITIES_JSON_PATH+"/"+ENTITYNAME_PORO+".png", "running");
    setEntitySprite(sprite);

    sprite->setPosition(sf::Vector2f(x,y));
    setHitboxes(info, sprite->getPosition());
    soundManager = SoundManager::getInstance();
}

Poro::~Poro() {
    delete sprite;
    sprite = NULL;
    setEntitySprite(NULL);
}

void Poro::update(sf::Time deltaTime) {
    sprite->update(deltaTime);
}

EntitySprite* Poro::getSprite() {
    return sprite;
}

void Poro::checkArea(std::map< std::string, Entity* >& entities) {
    sf::FloatRect zone = getCurrentHitbox(ANIMATIONS[state], sprite->getCurrentFrame()).getArea();
    zone.top -= PORO_DETECTION / 2;
    zone.left -= PORO_DETECTION / 2;
    zone.width += PORO_DETECTION;
    zone.height += PORO_DETECTION;
    sf::FloatRect elodie = ((Elodie*)entities["elodie"])->returnCurrentHitbox().getArea();
    sf::FloatRect portal = ((Portal*)entities["portal"])->returnCurrentHitbox().getArea();
    if (zone.intersects(elodie)) {
        if (elodie.left > getCurrentHitbox(ANIMATIONS[state], sprite->getCurrentFrame()).getArea().left)
            speed.x = -PORO_SPEED_X;
        else
            speed.x = PORO_SPEED_X;
    }
    if (zone.intersects(portal)) {
        if (speed.y == 0 && ((portal.left > getCurrentHitbox(ANIMATIONS[state], sprite->getCurrentFrame()).getArea().left && speed.x > 0) ||
            (portal.left < getCurrentHitbox(ANIMATIONS[state], sprite->getCurrentFrame()).getArea().left && speed.x < 0))) {
                speed.y = -PORO_SPEED_Y;
        }
    }
    if (portal.intersects(getCurrentHitbox(ANIMATIONS[state], sprite->getCurrentFrame()).getArea())) {
        life = 0;
    }
}


Hitbox Poro::returnCurrentHitbox() {
    return getCurrentHitbox(ANIMATIONS[state], sprite->getCurrentFrame());
}

void  Poro::takeDamage(int damage, bool ignore) {
    if (!damageCD && damage > 0) {
        life = 0;
        damageCD = DAMAGE_CD;
        soundManager->play(SoundType::SHEEP);
    }
}

void Poro::doStuff(EventHandler* const& event, std::vector< std::vector<TileSprite*> > const& tiles, std::map< std::string, Entity* >& entities, sf::Time animate) {
    //Compute the gravity
    computeGravity(animate);

    checkArea(entities);

    //Check the collisions, set the new distances and do the move
    Collide collideTiles = collideWithTiles(tiles, &speed, animate.asSeconds(), getCurrentHitbox(ANIMATIONS[state], sprite->getCurrentFrame()));
    setDistance(collideTiles);
    move(animate.asSeconds()*(speed.x), animate.asSeconds()*speed.y);
    sprite->update(animate);

    if (speed.y == 0 && ((speed.x > 0 && collideTiles.right["surface"]) || (speed.x < 0 && collideTiles.left["surface"]))) {
        speed.y = -PORO_SPEED_Y;
    }

    if (damageCD)
        --damageCD;
}

void Poro::pause() {
    sprite->pause();
}

void Poro::play() {
    sprite->play();
}
