#include "../../Score/ScoreManager.h"
#include "../../Sound/SoundManager.h"
#include "Alien.h"

const int Alien::DAMAGE = 25;
const int Alien::STEP = 5;
const int Alien::LIMIT_Y = 100;
const int Alien::SPEED_X = 0;
const std::map< int, std::string > Alien::ANIMATIONS =
{
    {Alien::State::STANDING, "standing"}
};

Alien::Alien() : Alien(sf::Vector2f(0, 0))
{
}

Alien::Alien(sf::Vector2f position) :
    Entity(position, EntityType::ENEMY, EntityName::ALIEN,
           ENTITYTYPE_ENEMY+"/"+ENTITYNAME_ALIEN+".png", "standing",
           Alien::ANIMATIONS, Alien::State::STANDING,
{-Alien::SPEED_X, 0}, 1, Alien::DAMAGE)
{
}

Alien::Alien(float x, float y) : Alien(sf::Vector2f(x, y))
{
}

Alien::~Alien()
{
}

void Alien::doAttack(std::map< std::string, Entity* >& entities)
{
    sf::FloatRect entity = getCurrentHitbox(animations.at(state), sprite->getCurrentFrame()).getArea();
    Elodie* elodie = (Elodie*) entities["elodie"];
    if (entity.intersects(elodie->returnCurrentHitbox().getArea()))
        elodie->takeDamage(DAMAGE, false);
}

void  Alien::takeDamage(int, bool)
{
    if (!damageCD && damage > 0)
    {
        life = 0;
        damageCD = DAMAGE_CD;
        SoundManager::getInstance().play(SoundType::ALIEN);
    }
    SoundManager::getInstance().play(SoundType::PUNCH);
    ScoreManager& sm = ScoreManager::getInstance();
    sm.addEnemyKilled(EnemyType::ALIEN);
}

void Alien::doStuff(const EventHandler&, const std::vector< std::vector<TileSprite*> >&,
                    std::map< std::string, Entity* >& entities, sf::Time animate)
{
    if (!charging)
    {
        charging = true;
        Elodie* elo = ((Elodie*) entities["elodie"]);
        sf::FloatRect eloArea = elo->returnCurrentHitbox().getArea();

        destX = elo->getPosition().x + eloArea.width;
        destY = elo->getPosition().y + eloArea.height;
    }

    move(animate.asSeconds()*(speed.x), animate.asSeconds()*speed.y);
    sprite->update(animate);

    sf::FloatRect hitbox = returnCurrentHitbox().getArea();
    float centerX = hitbox.left + hitbox.width/2;
    float centerY = hitbox.top + hitbox.height/2;

    speed.x = destX - centerX;
    speed.y = destY - centerY;

    doAttack(entities);

    if (damageCD)
    {
        --damageCD;
    }
}
