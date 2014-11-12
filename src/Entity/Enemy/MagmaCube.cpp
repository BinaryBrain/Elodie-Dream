#include "../../Score/ScoreManager.h"
#include "../../Sound/SoundManager.h"
#include "MagmaCube.h"

const int MagmaCube::DAMAGE = 25;
const int MagmaCube::JUMP_CD = 50;
const int MagmaCube::MOVE_X = 200;
const int MagmaCube::MOVE_Y = 400;

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

    life = 1;

    info = EntityManager::getInstance().getEnemyInfo(EntityType::ENEMY, EntityName::MAGMACUBE);

    y -= (info->height - BLOCK_SIZE);
    state = MagmaCubeState::STANDING;

    sprite = new EntitySprite(info, ENTITIES_JSON_PATH+"/"+ENTITYTYPE_ENEMY+"/"+ENTITYNAME_MAGMACUBE+".png", "standing");
    setEntitySprite(sprite);

    sprite->setPosition(sf::Vector2f(x,y));
    setHitboxes(info, sprite->getPosition());
}

MagmaCube::~MagmaCube() {
    delete sprite;
    setEntitySprite(NULL);
}

void MagmaCube::update(sf::Time deltaTime) {
    sprite->update(deltaTime);
}

EntitySprite* MagmaCube::getSprite() {
    return sprite;
}

void MagmaCube::doAttack(std::map< std::string, Entity* >& entities) {
    sf::FloatRect entity = getCurrentHitbox(ANIMATIONS[state], sprite->getCurrentFrame()).getArea();
    Elodie* elodie = (Elodie*) entities["elodie"];
    if (entity.intersects(elodie->returnCurrentHitbox().getArea())) {
        elodie->takeDamage(DAMAGE, false);
    }
}

Hitbox MagmaCube::returnCurrentHitbox() {
    return getCurrentHitbox(ANIMATIONS[state], sprite->getCurrentFrame());
}

void MagmaCube::takeDamage(int damage, bool) {
    if (!damageCD && damage > 0) {
        life = 0;
        damageCD = DAMAGE_CD;
    }
    SoundManager::getInstance().play(SoundType::PUNCH);
    ScoreManager& sm = ScoreManager::getInstance();
    sm.addEnemyKilled(EnemyType::MAGMACUBE);
}

void MagmaCube::jump() {
    if (!jumpCD && !speed.x && !speed.y) {
        speed.x = -MOVE_X;
        speed.y = -MOVE_Y;
    } else if (speed.y == 0 && !jumpCD) {
        SoundManager::getInstance().play(SoundType::MAGMACUBE);
        speed.x = 0;
        jumpCD = JUMP_CD;
    } else if (!speed.x && speed.y) {
        if (direction == Direction::LEFT) {
            direction = Direction::RIGHT;
            speed.x = -MOVE_X;
        } else if (direction == Direction::RIGHT) {
            direction = Direction::LEFT;
            speed.x = MOVE_X;
        }
    } else if (jumpCD > 0) {
        --jumpCD;
    }
}

void MagmaCube::doStuff(EventHandler* const&, std::vector< std::vector<TileSprite*> > const& tiles, std::map< std::string, Entity* >& entities, sf::Time animate) {
    //Compute the gravity
    computeGravity(animate);

    //Check the collisions, set the new distances and do the move
    Collide collideTiles = collideWithTiles(tiles, &speed, animate.asSeconds(), getCurrentHitbox(ANIMATIONS[state], sprite->getCurrentFrame()));
    setDistance(collideTiles);
    move(animate.asSeconds()*(speed.x), animate.asSeconds()*speed.y);
    sprite->update(animate);

    doAttack(entities);
    jump();

    if (damageCD)
        --damageCD;
}

void MagmaCube::pause() {
    sprite->pause();
}

void MagmaCube::play() {
    sprite->play();
}
