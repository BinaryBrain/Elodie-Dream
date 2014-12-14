#ifndef LASER_H_INCLUDED
#define LASER_H_INCLUDED

#include "../Entity.h"
#include "../../Sprite/EntitySprite.h"
#include "../../Include/Collide.h"
#include "../../Include/EntityInfo.h"
#include "../../EventHandler/EventHandler.h"
#include "../../EntityManager/EntityManager.h"
#include "../Elodie.h"

class Laser : public Entity
{
public:
    static const int DAMAGE;
    static const std::map< int, std::string > ANIMATIONS;

    enum State
    {
        WAITING,
        ACTIVATED,
        UNACTIVATED
    };

public:
    Laser();
    Laser(sf::Vector2f position);
    Laser(float x, float y);
    virtual ~Laser();

    void doAttack(std::map< std::string, Entity* >& entities);

    virtual void takeDamage(int damage, bool ignore);
    virtual void doStuff(const EventHandler& event, const std::vector< std::vector<TileSprite*> >& tiles,
                         std::map< std::string, Entity* >& entities, sf::Time animate);

private:
    bool activated = false;
};

#endif // LASER_H_INCLUDED
