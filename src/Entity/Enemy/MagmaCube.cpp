#include "../../Score/ScoreManager.h"
#include "../../Sound/SoundManager.h"
#include "MagmaCube.h"

const int MagmaCube::DAMAGE = 25;
const int MagmaCube::JUMP_CD = 50;
const int MagmaCube::MOVE_X = 200;
const int MagmaCube::MOVE_Y = 400;
const std::map< int, std::string > MagmaCube::ANIMATIONS =
{
    {MagmaCube::State::STANDING, "standing"}
};

MagmaCube::MagmaCube() : MagmaCube(sf::Vector2f(0, 0))
{
}

MagmaCube::MagmaCube(sf::Vector2f position) :
    Entity(position, EntityType::ENEMY, EntityName::MAGMACUBE,
           ENTITYTYPE_ENEMY+"/"+ENTITYNAME_MAGMACUBE+".png", "standing",
           MagmaCube::ANIMATIONS, MagmaCube::State::STANDING,
{0, 0}, 1, MagmaCube::DAMAGE)
{
}

MagmaCube::MagmaCube(float x, float y) : MagmaCube(sf::Vector2f(x, y))
{
}

MagmaCube::~MagmaCube()
{
}

void MagmaCube::doAttack(std::map< std::string, Entity* >& entities)
{
    sf::FloatRect entity = getCurrentHitbox(animations.at(state), sprite->getCurrentFrame()).getArea();
    Elodie* elodie = (Elodie*) entities["elodie"];
    if (entity.intersects(elodie->returnCurrentHitbox().getArea()))
    {
        elodie->takeDamage(DAMAGE, false);
    }
}

void MagmaCube::takeDamage(int damage, bool)
{
    if (!damageCD && damage > 0)
    {
        life = 0;
        damageCD = DAMAGE_CD;
    }
    SoundManager::getInstance().play(SoundType::PUNCH);
    ScoreManager& sm = ScoreManager::getInstance();
    sm.addEnemyKilled(EnemyType::MAGMACUBE);
}

void MagmaCube::jump()
{
    if (!jumpCD && !speed.x && !speed.y)
    {
        speed.x = -MOVE_X;
        speed.y = -MOVE_Y;
    }
    else if (speed.y == 0 && !jumpCD)
    {
        SoundManager::getInstance().play(SoundType::MAGMACUBE);
        speed.x = 0;
        jumpCD = JUMP_CD;
    }
    else if (!speed.x && speed.y)
    {
        if (direction == Direction::LEFT)
        {
            direction = Direction::RIGHT;
            speed.x = -MOVE_X;
        }
        else if (direction == Direction::RIGHT)
        {
            direction = Direction::LEFT;
            speed.x = MOVE_X;
        }
    }
    else if (jumpCD > 0)
    {
        --jumpCD;
    }
}

void MagmaCube::doStuff(const EventHandler&, const std::vector< std::vector<TileSprite*> >& tiles,
                        std::map< std::string, Entity* >& entities, sf::Time animate)
{
    //Compute the gravity
    computeGravity(animate);

    //Check the collisions, set the new distances and do the move
    Collide collideTiles = collideWithTiles(tiles, animate.asSeconds());
    setDistance(collideTiles);
    move(animate.asSeconds()*(speed.x), animate.asSeconds()*speed.y);
    sprite->update(animate);

    doAttack(entities);
    jump();

    if (damageCD)
        --damageCD;
}
