#include "../Sound/SoundManager.h"
#include "Poro.h"

const int Poro::SPEED_X = 255;
const int Poro::SPEED_Y = 300;
const int Poro::DETECTION = 350;

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

    info = EntityManager::getInstance().getEnemyInfo(EntityType::ELODIE, EntityName::PORO);

    y -= (info->height - BLOCK_SIZE);
    state = PoroState::RUNNING;

    sprite = new EntitySprite(info, ENTITIES_JSON_PATH+"/"+ENTITYNAME_PORO+".png", "running");
    setEntitySprite(sprite);

    sprite->setPosition(sf::Vector2f(x,y));
    setHitboxes(info, sprite->getPosition());
}

Poro::~Poro() {
    delete sprite;
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
    zone.top -= DETECTION / 2;
    zone.left -= DETECTION / 2;
    zone.width += DETECTION;
    zone.height += DETECTION;
    sf::FloatRect elodie = ((Elodie*)entities["elodie"])->returnCurrentHitbox().getArea();
    sf::FloatRect portal = ((Portal*)entities["portal"])->returnCurrentHitbox().getArea();
    if (zone.intersects(elodie)) {
        if (elodie.left > getCurrentHitbox(ANIMATIONS[state], sprite->getCurrentFrame()).getArea().left)
            speed.x = -SPEED_X;
        else
            speed.x = SPEED_X;
    }
    if (zone.intersects(portal)) {
        if (speed.y == 0 && ((portal.left > getCurrentHitbox(ANIMATIONS[state], sprite->getCurrentFrame()).getArea().left && speed.x > 0) ||
            (portal.left < getCurrentHitbox(ANIMATIONS[state], sprite->getCurrentFrame()).getArea().left && speed.x < 0))) {
                speed.y = -SPEED_Y - 50;
        }
    }
    if (portal.intersects(getCurrentHitbox(ANIMATIONS[state], sprite->getCurrentFrame()).getArea())) {
        life = 0;
    }
}


Hitbox Poro::returnCurrentHitbox() {
    return getCurrentHitbox(ANIMATIONS[state], sprite->getCurrentFrame());
}

void  Poro::takeDamage(int damage, bool) {
    if (!damageCD && damage > 0) {
        life = 0;
        damageCD = DAMAGE_CD;
	SoundManager::getInstance().play(SoundType::SHEEP);
    }
}

void Poro::doStuff(EventHandler* const&, std::vector< std::vector<TileSprite*> > const& tiles, std::map< std::string, Entity* >& entities, sf::Time animate) {
    checkArea(entities);

    //Compute the gravity
    computeGravity(animate);

    //Check the collisions, set the new distances and do the move
    Collide collideTiles = collideWithTiles(tiles, &speed, animate.asSeconds(), getCurrentHitbox(ANIMATIONS[state], sprite->getCurrentFrame()));
    setDistance(collideTiles);
    move(animate.asSeconds()*(speed.x), animate.asSeconds()*speed.y);
    sprite->update(animate);

    if (speed.y == 0 && ((speed.x > 0 && collideTiles.right["surface"]) || (speed.x < 0 && collideTiles.left["surface"]))) {
        speed.y = -SPEED_Y;
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
