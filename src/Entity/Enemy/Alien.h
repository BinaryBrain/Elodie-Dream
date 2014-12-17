#ifndef ALIEN_H_INCLUDED
#define ALIEN_H_INCLUDED

#include "../Entity.h"
#include "../../Sprite/EntitySprite.h"
#include "../../Include/Collide.h"
#include "../../Include/EntityInfo.h"
#include "../../EventHandler/EventHandler.h"
#include "../../EntityManager/EntityManager.h"
#include "../Elodie.h"

class Alien : public Entity
{
public:
    static const int DAMAGE;
    static const int STEP;
    static const int LIMIT_Y;
    static const int SPEED_X;
    static const std::map< int, std::string > ANIMATIONS;

    enum State
    {
        STANDING
    };

public:
    Alien();
    Alien(sf::Vector2f position);
    Alien(float x, float y);
    virtual ~Alien();

    void doAttack(std::map< std::string, Entity* >& entities);

    virtual void takeDamage(int damage, bool ignore);
    virtual void doStuff(const EventHandler& event, const std::vector< std::vector<TileSprite*> >& tiles,
                         std::map< std::string, Entity* >& entities, sf::Time animate);

private:
    int limitSpeed = LIMIT_Y;
    int step = STEP;
    bool charging = false;
    float destX = 0;
    float destY = 0;
};

#endif // ALIEN_H_INCLUDED
