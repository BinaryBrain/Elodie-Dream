#include "../../Sound/SoundManager.h"
#include "Spikes.h"

const int Spikes::DAMAGE = 50;
const std::map< int, std::string > Spikes::ANIMATIONS =
{
    {Spikes::State::WAITING, "waiting"},
    {Spikes::State::ACTIVATED, "activated"},
    {Spikes::State::UNACTIVATED, "unactivated"}
};

Spikes::Spikes() : Spikes(sf::Vector2f(0, 0))
{
}

Spikes::Spikes(sf::Vector2f position) :
    Entity(position, EntityType::ENEMY, EntityName::SPIKES,
           ENTITYTYPE_ENEMY+"/"+ENTITYNAME_SPIKES+".png", "waiting",
           Spikes::ANIMATIONS, Spikes::State::WAITING,
{0, 0}, 1, Spikes::DAMAGE)
{
}

Spikes::Spikes(float x, float y) : Spikes(sf::Vector2f(x, y))
{
}

Spikes::~Spikes()
{
}

void Spikes::doAttack(std::map< std::string, Entity* >& entities)
{
    sf::FloatRect entity = getCurrentHitbox(animations.at(state), sprite->getCurrentFrame()).getArea();
    Elodie* elodie = (Elodie*) entities["elodie"];
    if (state == Spikes::State::ACTIVATED && sprite->getCurrentFrame() == 2 &&
            entity.intersects(elodie->returnCurrentHitbox().getArea()))
    {
        elodie->takeDamage(DAMAGE, true);
    }
    if (!activated && entity.intersects(elodie->returnCurrentHitbox().getArea()))
    {
        state = Spikes::State::ACTIVATED;
        changeStance(animations.at(state), sf::seconds(0.05f));
        activated = true;

        SoundManager::getInstance().play(SoundType::SPIKES);
    }
}

void  Spikes::takeDamage(int, bool)
{
}

void Spikes::doStuff(const EventHandler&, const std::vector< std::vector<TileSprite*> >&,
                     std::map< std::string, Entity* >& entities, sf::Time animate)
{
    doAttack(entities);

    if (state == Spikes::State::ACTIVATED && sprite->getCurrentFrame() == 3)
    {
        state = Spikes::State::UNACTIVATED;
        changeStance(animations.at(state), sf::seconds(0.05f));
    }

    sprite->update(animate);
}
