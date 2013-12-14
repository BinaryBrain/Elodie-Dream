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
    sprite->changeStance(ANIMATIONS[state], sf::seconds(0.05f));
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

void Bristle::checkArea(std::map< std::string, Entity* >& entities) {
    sf::FloatRect zone = getCurrentHitbox(ANIMATIONS[state], sprite->getCurrentFrame()).getArea();
    zone.top -= BRISTLE_DETECTION / 2;
    zone.left -= BRISTLE_DETECTION / 2;
    zone.width += BRISTLE_DETECTION;
    zone.height += BRISTLE_DETECTION;
    sf::FloatRect elodie = ((Elodie*)entities["elodie"])->returnCurrentHitbox().getArea();
    if (zone.intersects(elodie) && !speed.x && !speed.y) {
        if (!charge) {
            soundManager->play(SoundType::BRISTLE);
        }
        if (elodie.left > getCurrentHitbox(ANIMATIONS[state], sprite->getCurrentFrame()).getArea().left)
            speed.x = BRISTLE_SPEED_X;
        else
            speed.x = -BRISTLE_SPEED_X;
        speed.y = -BRISTLE_SPEED_Y;
        charge = true;
    }
}

void  Bristle::takeDamage(int damage, bool ignore) {
    if (!damageCD && damage > 0) {
        life = 0;
        damageCD = DAMAGE_CD;
    }
}

void Bristle::doStuff(EventHandler* const& event, std::vector< std::vector<TileSprite*> > const& tiles, std::map< std::string, Entity* >& entities, sf::Time animate) {
    checkArea(entities);

    //Compute the gravity
    computeGravity(animate);

    //Check the collisions, set the new distances and do the move
    Collide collideTiles = collideWithTiles(tiles, &speed, animate.asSeconds(), getCurrentHitbox(ANIMATIONS[state], sprite->getCurrentFrame()));
    setDistance(collideTiles);
    move(animate.asSeconds()*(speed.x), animate.asSeconds()*speed.y);
    if (speed.x || speed.y) {
        sprite->update(animate);
    }

    if (!speed.x && charge) {
        if (direction == Direction::LEFT) {
            direction = Direction::RIGHT;
            speed.x = -BRISTLE_SPEED_X;
        } else if (direction == Direction::RIGHT) {
            direction = Direction::LEFT;
            speed.x = BRISTLE_SPEED_X;
        }
    }
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
