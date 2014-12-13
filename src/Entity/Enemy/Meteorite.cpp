#include "Meteorite.h"

const int Meteorite::DAMAGE = 70;
const int Meteorite::SPEED_X = 100;
const int Meteorite::SPEED_Y = 100;
const std::map< int, std::string > Meteorite::ANIMATIONS =
{
    {Meteorite::State::STANDING, "standing"}
};

Meteorite::Meteorite() : Meteorite(sf::Vector2f(0, 0))
{
}

Meteorite::Meteorite(sf::Vector2f position) :
    Entity(position, EntityType::ENEMY, EntityName::SHEEP,
           ENTITYTYPE_ENEMY+"/"+""+".png", "standing",
           Meteorite::ANIMATIONS, Meteorite::State::STANDING,
{-Meteorite::SPEED_X, 0}, 1, Meteorite::DAMAGE)
{
}

Meteorite::Meteorite(float x, float y) : Meteorite(sf::Vector2f(x, y))
{
}

Meteorite::~Meteorite()
{
}

void Meteorite::doAttack(std::map< std::string, Entity* >& entities)
{
    sf::FloatRect entity = getCurrentHitbox(animations.at(state), sprite->getCurrentFrame()).getArea();
    Elodie* elodie = (Elodie*) entities["elodie"];
    if (entity.intersects(elodie->returnCurrentHitbox().getArea()))
        elodie->takeDamage(DAMAGE, false);
}

void  Meteorite::takeDamage(int, bool)
{
}

void Meteorite::doStuff(const EventHandler&, const std::vector< std::vector<TileSprite*> >&,
                    std::map< std::string, Entity* >& entities, sf::Time animate)
{
    move(animate.asSeconds()*(Meteorite::SPEED_X), animate.asSeconds()*Meteorite::SPEED_Y);
    sprite->update(animate);
    doAttack(entities);

    if (damageCD)
    {
        --damageCD;
    }
}
