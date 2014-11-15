#ifndef BONUS_H_INCLUDED
#define BONUS_H_INCLUDED

#include "../const.h"
#include "Entity.h"
#include "../Sprite/EntitySprite.h"
#include "../Include/Collide.h"
#include "../Include/EntityInfo.h"
#include "../EventHandler/EventHandler.h"
#include "../EntityManager/EntityManager.h"
#include "Elodie.h"

class Bonus : public Entity
{
public:
    static const int POINTS;
    static const std::map< int, std::string > ANIMATIONS;

    enum State
    {
        STANDING
    };

public:
    Bonus();
    Bonus(sf::Vector2f position);
    Bonus(float x, float y);
    virtual ~Bonus();

    void getTaken(std::map< std::string, Entity* >& entities);

    virtual void takeDamage(int damage, bool ignore);
    virtual void doStuff(const EventHandler& event, const std::vector< std::vector<TileSprite*> >& tiles,
                         std::map< std::string, Entity* >& entities, sf::Time animate);
};

#endif // BONUS_H_INCLUDED
