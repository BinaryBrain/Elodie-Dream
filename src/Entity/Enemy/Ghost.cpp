#include "Ghost.h"

const int Ghost::DAMAGE = 12;
const int Ghost::STEP = 5;
const int Ghost::LIMIT_Y = 150;
const int Ghost::SPEED_X = 100;
const std::map< int, std::string > Ghost::ANIMATIONS =
{
    {Ghost::State::STANDING, "standing"}
};

Ghost::Ghost() : Ghost(sf::Vector2f(0, 0))
{
}

Ghost::Ghost(sf::Vector2f position) :
    Entity(position, EntityType::ENEMY, EntityName::GHOST,
           ENTITYTYPE_ENEMY+"/"+ENTITYNAME_GHOST+".png", "standing",
           Ghost::ANIMATIONS, Ghost::State::STANDING,
{-Ghost::SPEED_X, 0}, 1, Ghost::DAMAGE)
{
}

Ghost::Ghost(float x, float y) : Ghost(sf::Vector2f(x, y))
{
}

Ghost::~Ghost()
{
}

void Ghost::doAttack(std::map< std::string, Entity* >& entities)
{
    sf::FloatRect entity = getCurrentHitbox(animations.at(state), sprite->getCurrentFrame()).getArea();
    Elodie* elodie = (Elodie*) entities["elodie"];
    if (entity.intersects(elodie->returnCurrentHitbox().getArea()))
        elodie->takeDamage(DAMAGE, false);
}

void  Ghost::takeDamage(int, bool)
{
}

void Ghost::doStuff(const EventHandler&, const std::vector< std::vector<TileSprite*> >&,
                    std::map< std::string, Entity* >& entities, sf::Time animate)
{
    move(animate.asSeconds()*(speed.x), animate.asSeconds()*speed.y);
    sprite->update(animate);

    if (speed.y < 0 && speed.y < -limitSpeed)
    {
        step = STEP;
    }
    else if (speed.y > 0 && speed.y > limitSpeed)
    {
        step = -STEP;
    }
    speed.y += step;

    doAttack(entities);

    if (damageCD)
    {
        --damageCD;
    }
}
