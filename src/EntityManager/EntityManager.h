#ifndef ENTITYMANAGER_H_INCLUDED
#define ENTITYMANAGER_H_INCLUDED

#include <map>
#include <string>
#include "../const.h"
#include "../Include/EntityInfo.h"
#include "SFML/Graphics.hpp"

enum class EntityName {
    ELODIE, SHEEP
};

enum class EntityType {
    ELODIE, ENEMY
};

typedef std::map< EntityType, std::map< EntityName, EntityInfo* > > EntityBox;

class EntityManager {
public:
    EntityManager();
    virtual ~EntityManager();

    EntityInfo* getEnemyInfo(EntityType type, EntityName name);
protected:
private:
    std::string getPath(EntityType type, EntityName name);

     EntityBox enemies;

    std::map< EntityName, std::string > ENTITY_NAME;
    std::map< EntityType, std::string > ENTITY_TYPE;
};


#endif // ENTITYMANAGER_H_INCLUDED
