#ifndef ENTITYMANAGER_H_INCLUDED
#define ENTITYMANAGER_H_INCLUDED

#include <map>
#include <string>
#include "../const.h"
#include "../Include/EntityInfo.h"
#include "SFML/Graphics.hpp"
#include "../Json/JsonAccessor.h"

enum class EntityName
{
    ELODIE, SHEEP, MAGMACUBE, BRISTLE, GHOST, SPIKES, PORTAL, PORO, SPRITE, METEORITE, LASER, ALIEN, RAVEN, ROCKET
};

enum class EntityType
{
    ELODIE, ENEMY, MISC, BONUS
};

typedef std::map< EntityType, std::map< EntityName, EntityInfo* > > EntityBox;

class EntityManager
{
public:
    static EntityManager& getInstance();
    EntityInfo* getEnemyInfo(EntityType type, EntityName name);

private:
    EntityManager();
    virtual ~EntityManager();

    EntityManager(const EntityManager&);
    EntityManager& operator= (EntityManager const&); // Makes operator= private

    std::string getPath(EntityType type, EntityName name);

    EntityBox enemies;

    std::map< EntityName, std::string > ENTITY_NAME;
    std::map< EntityType, std::string > ENTITY_TYPE;
};


#endif // ENTITYMANAGER_H_INCLUDED
