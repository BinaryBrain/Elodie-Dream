#ifndef PORO_H_INCLUDED
#define PORO_H_INCLUDED

#include "Entity.h"
#include "../Sprite/EntitySprite.h"
#include "../Include/Collide.h"
#include "../Include/EntityInfo.h"
#include "../EventHandler/EventHandler.h"
#include "../EntityManager/EntityManager.h"
#include "Elodie.h"

class Poro : public Entity
{
public:
    static const int SPEED_X;
    static const int SPEED_Y;
    static const int DETECTION;
    static const std::map< int, std::string > ANIMATIONS;

    enum State
    {
        RUNNING
    };

public:
    Poro();
    Poro(sf::Vector2f position);
    Poro(float x, float y);
    virtual ~Poro();

    void checkArea(std::map< std::string, Entity* >& entities);

    virtual void takeDamage(int damage, bool ignore);
    virtual void doStuff(const EventHandler& event, const std::vector< std::vector<TileSprite*> >& tiles,
                         std::map< std::string, Entity* >& entities, sf::Time animate);
};

#endif // PORO_H_INCLUDED
