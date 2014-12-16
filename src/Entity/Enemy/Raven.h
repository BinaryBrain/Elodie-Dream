#ifndef RAVEN_H_INCLUDED
#define RAVEN_H_INCLUDED

#include "../Entity.h"
#include "../../Sprite/EntitySprite.h"
#include "../../Include/Collide.h"
#include "../../Include/EntityInfo.h"
#include "../../EventHandler/EventHandler.h"
#include "../../EntityManager/EntityManager.h"
#include "../Elodie.h"

class Raven : public Entity
{
public:
    static const int DAMAGE;
    static const int SPEED_Y_MULT;
    static const int STANDING_SPEED_X;
    static const int ATTACK_SPEED_X;
    static const int DETECTION_X;
    static const int DETECTION_Y;

    static const std::map< int, std::string > ANIMATIONS;

    enum State
    {
        STANDING
    };

public:
    Raven();
    Raven(sf::Vector2f position);
    Raven(float x, float y);
    virtual ~Raven();

    bool checkCharge(std::map< std::string, Entity* >& entities);
    void doAttack(std::map< std::string, Entity* >& entities);

    virtual void takeDamage(int damage, bool ignore);
    virtual void doStuff(const EventHandler& event, const std::vector< std::vector<TileSprite*> >& tiles,
                         std::map< std::string, Entity* >& entities, sf::Time animate);

    bool chargeSoundPlayed = false;
};

#endif // RAVEN_H_INCLUDED
