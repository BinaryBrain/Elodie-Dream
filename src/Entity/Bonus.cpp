#include "../Score/ScoreManager.h"
#include "../Sound/SoundManager.h"
#include "Bonus.h"

const int Bonus::POINTS = 50;
const std::map< int, std::string > Bonus::ANIMATIONS =
{
    {Bonus::State::STANDING, "standing"}
};

Bonus::Bonus() : Bonus(sf::Vector2f(0, 0))
{
}

Bonus::Bonus(sf::Vector2f position) :
    Entity(position, EntityType::BONUS, EntityName::SPRITE,
           ENTITYTYPE_BONUS + "/" + ENTITYNAME_SPRITE + ".png", "standing",
           Bonus::ANIMATIONS, Bonus::State::STANDING,
{0, 0}, 1, 0)
{
}

Bonus::Bonus(float x, float y) : Bonus(sf::Vector2f(x, y))
{
}

Bonus::~Bonus()
{
}

void Bonus::takeDamage(int, bool)
{
}

void Bonus::getTaken(std::map< std::string, Entity* >& entities)
{
    sf::FloatRect zone = getCurrentHitbox(animations.at(state), sprite->getCurrentFrame()).getArea();
    sf::FloatRect elodie = ((Elodie*)entities["elodie"])->returnCurrentHitbox().getArea();
    if (zone.intersects(elodie))
    {
        ScoreManager& sm = ScoreManager::getInstance();
        sm.takeBonus();
        life = 0;
        SoundManager::getInstance().play(SoundType::BOTTLE);
    }
}

void Bonus::doStuff(const EventHandler&, const std::vector< std::vector<TileSprite*> >&,
                    std::map< std::string, Entity* >& entities, sf::Time animate)
{
    getTaken(entities);
    update(animate);
}
