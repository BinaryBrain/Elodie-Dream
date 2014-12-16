#ifndef Portal_H_INCLUDED
#define Portal_H_INCLUDED

#include "../const.h"
#include "Entity.h"
#include "../Sprite/EntitySprite.h"
#include "../Include/Collide.h"
#include "../Include/EntityInfo.h"
#include "../EventHandler/EventHandler.h"
#include "../EntityManager/EntityManager.h"
#include "Elodie.h"

class Portal : public Entity
{
public:
    static const std::map< int, std::string > ANIMATIONS;

    enum State
    {
        STANDING
    };

public:
    Portal();
    Portal(sf::Vector2f position, std::string entityType, std::string entityName, EntityType type, EntityName name);
    Portal(float x, float y, std::string entityType, std::string entityName, EntityType type, EntityName name);
    virtual ~Portal();

    virtual void takeDamage(int damage, bool ignore);
    virtual void doStuff(const EventHandler& event, const std::vector< std::vector<TileSprite*> >& tiles,
                         std::map< std::string, Entity* >& entities, sf::Time animate);
};

#endif // Portal_H_INCLUDED
