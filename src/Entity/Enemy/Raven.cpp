#include "../../Score/ScoreManager.h"
#include "../../Sound/SoundManager.h"
#include "Raven.h"

const int Raven::DAMAGE = 20;
const int Raven::SPEED_Y_MULT = 4;
const int Raven::STANDING_SPEED_X = 50;
const int Raven::ATTACK_SPEED_X = 150;
const int Raven::DETECTION_X = 350;
const int Raven::DETECTION_Y = 300;

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
        // SoundManager::getInstance().play(SoundType::RAVEN); // TODO : Reactivate sound when file added
    }
    SoundManager::getInstance().play(SoundType::PUNCH);
    ScoreManager& sm = ScoreManager::getInstance();
    sm.addEnemyKilled(EnemyType::RAVEN);
}

bool Raven::checkCharge(std::map< std::string, Entity* >& entities) {
    sf::FloatRect elo = ((Elodie*) entities["elodie"])->returnCurrentHitbox().getArea();
    sf::FloatRect me = returnCurrentHitbox().getArea();

    return (abs(elo.left - me.left) < DETECTION_X && abs(elo.top - me.top) < DETECTION_Y);
}

void Raven::doStuff(const EventHandler&, const std::vector< std::vector<TileSprite*> >&,
                    std::map< std::string, Entity* >& entities, sf::Time animate)
{
    speed.x = -STANDING_SPEED_X;

    if (checkCharge(entities))
    {
        if (!chargeSoundPlayed)
        {
            SoundManager::getInstance().play(SoundType::RAVEN);
        }
        sf::FloatRect eloArea = ((Elodie*) entities["elodie"])->returnCurrentHitbox().getArea();
        float targetY = eloArea.top + eloArea.height/4;
        float myY = returnCurrentHitbox().getArea().top;

        speed.x = -ATTACK_SPEED_X;
        speed.y = (targetY - myY) * SPEED_Y_MULT;
        chargeSoundPlayed = true;;
    }
    else
    {
        chargeSoundPlayed = false;
    }

    move(animate.asSeconds()*(speed.x), animate.asSeconds()*(speed.y));
    sprite->update(animate);

    doAttack(entities);

    if (damageCD)
    {
        --damageCD;
    }
}
