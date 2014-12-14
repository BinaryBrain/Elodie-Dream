#include "../../Score/ScoreManager.h"
#include "../../Sound/SoundManager.h"
#include "Raven.h"

const int Raven::DAMAGE = 10;
const std::map< int, std::string > Raven::ANIMATIONS =
{
    {Raven::State::STANDING, "standing"}
};

Raven::Raven() : Raven(sf::Vector2f(0, 0))
{
}

Raven::Raven(sf::Vector2f position) :
    Entity(position, EntityType::ENEMY, EntityName::RAVEN,
           ENTITYTYPE_ENEMY+"/"+ENTITYNAME_RAVEN+".png", "standing",
           Raven::ANIMATIONS, Raven::State::STANDING,
{0, 0}, 1, Raven::DAMAGE)
{
}

Raven::Raven(float x, float y) : Raven(sf::Vector2f(x, y))
{
}

Raven::~Raven()
{
}

void Raven::doAttack(std::map< std::string, Entity* >& entities)
{
    sf::FloatRect entity = getCurrentHitbox(animations.at(state), sprite->getCurrentFrame()).getArea();
    Elodie* elodie = (Elodie*) entities["elodie"];
    if (entity.intersects(elodie->returnCurrentHitbox().getArea()))
    {
        elodie->takeDamage(DAMAGE, false);
    }
}

void Raven::takeDamage(int damage, bool)
{
    if (!damageCD && damage > 0)
    {
        life = 0;
        damageCD = DAMAGE_CD;
        SoundManager::getInstance().play(SoundType::RAVEN);
    }
    SoundManager::getInstance().play(SoundType::PUNCH);
    ScoreManager& sm = ScoreManager::getInstance();
    sm.addEnemyKilled(EnemyType::RAVEN);
}

void Raven::doStuff(const EventHandler&, const std::vector< std::vector<TileSprite*> >& tiles,
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

    if (damageCD)
    {
        --damageCD;
    }
}
