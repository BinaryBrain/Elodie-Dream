#include "../Sound/SoundManager.h"
#include "Poro.h"

const int Poro::SPEED_X = 255;
const int Poro::SPEED_Y = 300;
const int Poro::DETECTION = 350;
const std::map< int, std::string > Poro::ANIMATIONS =
{
    {Poro::State::RUNNING, "running"}
};

Poro::Poro() : Poro(sf::Vector2f(0, 0))
{
}

Poro::Poro(sf::Vector2f position) :
    Entity(position, EntityType::ELODIE, EntityName::PORO,
           ENTITYNAME_PORO + ".png", "running",
           Poro::ANIMATIONS, Poro::State::RUNNING,
{0, 0}, 1, 0)
{
}

Poro::Poro(float x, float y) : Poro(sf::Vector2f(x, y))
{
}

Poro::~Poro()
{
}

void Poro::checkArea(std::map< std::string, Entity* >& entities)
{
    sf::FloatRect zone = getCurrentHitbox(animations.at(state), sprite->getCurrentFrame()).getArea();
    zone.top -= DETECTION / 2;
    zone.left -= DETECTION / 2;
    zone.width += DETECTION;
    zone.height += DETECTION;
    sf::FloatRect elodie = ((Elodie*)entities["elodie"])->returnCurrentHitbox().getArea();
    sf::FloatRect portal = ((Portal*)entities["portal"])->returnCurrentHitbox().getArea();
    if (zone.intersects(elodie))
    {
        if (elodie.left > getCurrentHitbox(animations.at(state), sprite->getCurrentFrame()).getArea().left)
            speed.x = -SPEED_X;
        else
            speed.x = SPEED_X;
    }
    if (zone.intersects(portal))
    {
        if (speed.y == 0 && ((portal.left > getCurrentHitbox(animations.at(state), sprite->getCurrentFrame()).getArea().left && speed.x > 0) ||
                             (portal.left < getCurrentHitbox(animations.at(state), sprite->getCurrentFrame()).getArea().left && speed.x < 0)))
        {
            speed.y = -SPEED_Y - 50;
        }
    }
    if (portal.intersects(getCurrentHitbox(animations.at(state), sprite->getCurrentFrame()).getArea()))
    {
        life = 0;
    }
}


void  Poro::takeDamage(int damage, bool)
{
    if (!damageCD && damage > 0)
    {
        life = 0;
        damageCD = DAMAGE_CD;
        SoundManager::getInstance().play(SoundType::SHEEP);
    }
}

void Poro::doStuff(const EventHandler&, std::vector< std::vector<TileSprite*> > const& tiles, std::map< std::string, Entity* >& entities, sf::Time animate)
{
    checkArea(entities);

    //Compute the gravity
    computeGravity(animate);

    //Check the collisions, set the new distances and do the move
    Collide collideTiles = collideWithTiles(tiles, animate.asSeconds());
    setDistance(collideTiles);
    move(animate.asSeconds()*(speed.x), animate.asSeconds()*speed.y);
    sprite->update(animate);

    if (speed.y == 0 && ((speed.x > 0 && collideTiles.right["surface"]) || (speed.x < 0 && collideTiles.left["surface"])))
    {
        speed.y = -SPEED_Y;
    }

    if (damageCD)
        --damageCD;
}
