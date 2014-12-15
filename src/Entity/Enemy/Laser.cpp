#include "../../Sound/SoundManager.h"
#include "Laser.h"

const int Laser::DAMAGE = 50;
const std::map< int, std::string > Laser::ANIMATIONS =
{
    {Laser::State::WAITING, "waiting"},
    {Laser::State::ACTIVATED, "activated"},
    {Laser::State::UNACTIVATED, "unactivated"}
};

Laser::Laser() : Laser(sf::Vector2f(0, 0))
{
}

Laser::Laser(sf::Vector2f position) :
    Entity(position, EntityType::ENEMY, EntityName::LASER,
           ENTITYTYPE_ENEMY+"/"+ENTITYNAME_LASER+".png", "waiting",
           Laser::ANIMATIONS, Laser::State::WAITING,
{0, 0}, 1, Laser::DAMAGE)
{
}

Laser::Laser(float x, float y) : Laser(sf::Vector2f(x, y))
{
}

Laser::~Laser()
{
}

void Laser::doAttack(std::map< std::string, Entity* >& entities)
{
    sf::FloatRect entity = getCurrentHitbox(animations.at(state), sprite->getCurrentFrame()).getArea();
    Elodie* elodie = (Elodie*) entities["elodie"];
    if (state == Laser::State::ACTIVATED && sprite->getCurrentFrame() == 2 &&
            entity.intersects(elodie->returnCurrentHitbox().getArea()))
    {
        elodie->takeDamage(DAMAGE, true);
    }
    if (!activated && entity.intersects(elodie->returnCurrentHitbox().getArea()))
    {
        state = Laser::State::ACTIVATED;
        changeStance(animations.at(state), sf::seconds(0.05f));
        activated = true;

        SoundManager::getInstance().play(SoundType::LASER);
    }
}

void  Laser::takeDamage(int, bool)
{
}

void Laser::doStuff(const EventHandler&, const std::vector< std::vector<TileSprite*> >&,
                     std::map< std::string, Entity* >& entities, sf::Time animate)
{
    doAttack(entities);

    if (state == Laser::State::ACTIVATED && sprite->getCurrentFrame() == 3)
    {
        state = Laser::State::UNACTIVATED;
        changeStance(animations.at(state), sf::seconds(0.05f));
    }

    sprite->update(animate);
}
