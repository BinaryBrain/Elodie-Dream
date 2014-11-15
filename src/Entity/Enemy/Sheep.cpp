#include "../../Score/ScoreManager.h"
#include "../../Sound/SoundManager.h"
#include "Sheep.h"

const int Sheep::DAMAGE = 10;
const std::map< int, std::string > Sheep::ANIMATIONS =
{
    {Sheep::State::STANDING, "standing"}
};

Sheep::Sheep() : Sheep(sf::Vector2f(0, 0))
{
}

Sheep::Sheep(sf::Vector2f position) :
    Entity(position, EntityType::ENEMY, EntityName::SHEEP,
           ENTITYTYPE_ENEMY+"/"+ENTITYNAME_SHEEP+".png", "standing",
           Sheep::ANIMATIONS, Sheep::State::STANDING,
{0, 0}, 1, Sheep::DAMAGE)
{
}

Sheep::Sheep(float x, float y) : Sheep(sf::Vector2f(x, y))
{
}

Sheep::~Sheep()
{
}

void Sheep::doAttack(std::map< std::string, Entity* >& entities)
{
    sf::FloatRect entity = getCurrentHitbox(animations.at(state), sprite->getCurrentFrame()).getArea();
    Elodie* elodie = (Elodie*) entities["elodie"];
    if (entity.intersects(elodie->returnCurrentHitbox().getArea()))
    {
        elodie->takeDamage(DAMAGE, false);
    }
}

void Sheep::takeDamage(int damage, bool)
{
    if (!damageCD && damage > 0)
    {
        life = 0;
        damageCD = DAMAGE_CD;
        SoundManager::getInstance().play(SoundType::SHEEP);
    }
    SoundManager::getInstance().play(SoundType::PUNCH);
    ScoreManager& sm = ScoreManager::getInstance();
    sm.addEnemyKilled(EnemyType::SHEEP);
}

void Sheep::doStuff(const EventHandler&, const std::vector< std::vector<TileSprite*> >& tiles,
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
