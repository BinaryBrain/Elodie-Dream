#ifndef METEORITE_H_INCLUDED
#define METEORITE_H_INCLUDED

#include "../Entity.h"
#include "../../Sprite/EntitySprite.h"
#include "../../Include/Collide.h"
#include "../../Include/EntityInfo.h"
#include "../../EventHandler/EventHandler.h"
#include "../../EntityManager/EntityManager.h"
#include "../Elodie.h"

class Meteorite : public Entity
{
public:
    static const int DAMAGE;
    static const int SPEED_X;
    static const int SPEED_Y;
    static const int ACCELERATION;
    static const std::map< int, std::string > ANIMATIONS;

    enum State
    {
        STANDING
    };

public:
    Meteorite();
    Meteorite(sf::Vector2f position);
    Meteorite(float x, float y);
    virtual ~Meteorite();

    void doAttack(std::map< std::string, Entity* >& entities);

    virtual void takeDamage(int damage, bool ignore);
    virtual void doStuff(const EventHandler& event, const std::vector< std::vector<TileSprite*> >& tiles,
                         std::map< std::string, Entity* >& entities, sf::Time animate);

private:
    int framesSinceStart = 0;
};

#endif // METEORITE_H_INCLUDED
