#ifndef SPIKES_H_INCLUDED
#define SPIKES_H_INCLUDED

#include "../Entity.h"
#include "../../Sprite/EntitySprite.h"
#include "../../Include/Collide.h"
#include "../../Include/EntityInfo.h"
#include "../../EventHandler/EventHandler.h"
#include "../../EntityManager/EntityManager.h"
#include "../Elodie.h"

class Spikes : public Entity
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
    Spikes();
    Spikes(sf::Vector2f position);
    Spikes(float x, float y);
    virtual ~Spikes();

    void doAttack(std::map< std::string, Entity* >& entities);

    virtual void takeDamage(int damage, bool ignore);
    virtual void doStuff(const EventHandler& event, const std::vector< std::vector<TileSprite*> >& tiles,
                         std::map< std::string, Entity* >& entities, sf::Time animate);

private:
    bool activated = false;
};

#endif // SPIKES_H_INCLUDED
