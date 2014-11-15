#include "../../Score/ScoreManager.h"
#include "../../Sound/SoundManager.h"
#include "Bristle.h"

const int Bristle::DAMAGE = 60;
const int Bristle::SPEED_X = 500;
const int Bristle::SPEED_Y = 200;
const int Bristle::DETECTION = 450;
const std::map< int, std::string > Bristle::ANIMATIONS =
{
    {Bristle::State::STANDING, "standing"},
    {Bristle::State::GRATTING, "gratting"}
};

Bristle::Bristle() : Bristle(sf::Vector2f(0, 0))
{
}

Bristle::Bristle(sf::Vector2f position) :
    Entity(position, EntityType::ENEMY, EntityName::BRISTLE,
           ENTITYTYPE_ENEMY+"/"+ENTITYNAME_BRISTLE+".png", "gratting",
           Bristle::ANIMATIONS, Bristle::State::GRATTING,
{0, 0}, 1, Bristle::DAMAGE)
{
}

Bristle::Bristle(float x, float y) : Bristle(sf::Vector2f(x, y))
{
}

Bristle::~Bristle()
{
}

void Bristle::doAttack(std::map< std::string, Entity* >& entities)
{
    sf::FloatRect entity = getCurrentHitbox(animations.at(state), sprite->getCurrentFrame()).getArea();
    Elodie* elodie = (Elodie*) entities["elodie"];
    if (entity.intersects(elodie->returnCurrentHitbox().getArea()))
        elodie->takeDamage(DAMAGE, false);
}

void Bristle::checkArea(std::map< std::string, Entity* >& entities)
{
    sf::FloatRect zone = getCurrentHitbox(animations.at(state), sprite->getCurrentFrame()).getArea();
    zone.top -= DETECTION / 4;
    zone.left -= DETECTION / 2;
    zone.width += DETECTION;
    zone.height += DETECTION / 2;
    sf::FloatRect elodie = ((Elodie*)entities["elodie"])->returnCurrentHitbox().getArea();
    if (zone.intersects(elodie) && !speed.x && !speed.y)
    {
        if (!charge)
        {
            SoundManager::getInstance().play(SoundType::BRISTLE);
        }
        if (elodie.left > getCurrentHitbox(animations.at(state), sprite->getCurrentFrame()).getArea().left)
            speed.x = SPEED_X;
        else
            speed.x = -SPEED_X;
        speed.y = -SPEED_Y;

        state = Bristle::State::STANDING;
        changeStance(animations.at(state), sf::seconds(0.05f));
        charge = true;
    }
}

void Bristle::takeDamage(int damage, bool)
{
    if (!damageCD && damage > 0)
    {
        life = 0;
        damageCD = DAMAGE_CD;
    }
    SoundManager::getInstance().play(SoundType::PUNCH);
    ScoreManager& sm = ScoreManager::getInstance();
    sm.addEnemyKilled(EnemyType::BRISTLE);
}

void Bristle::doStuff(const EventHandler&, const std::vector< std::vector<TileSprite*> >& tiles,
                      std::map< std::string, Entity* >& entities, sf::Time animate)
{
    checkArea(entities);

    //Compute the gravity
    computeGravity(animate);

    //Check the collisions, set the new distances and do the move
    Collide collideTiles = collideWithTiles(tiles, animate.asSeconds());
    setDistance(collideTiles);
    move(animate.asSeconds()*(speed.x), animate.asSeconds()*speed.y);
    sprite->update(animate);

    if (!speed.x && charge)
    {
        if (direction == Direction::LEFT)
        {
            direction = Direction::RIGHT;
            speed.x = -SPEED_X;
        }
        else if (direction == Direction::RIGHT)
        {
            direction = Direction::LEFT;
            speed.x = SPEED_X;
        }
    }
    doAttack(entities);

    if (damageCD)
    {
        --damageCD;
    }
}
