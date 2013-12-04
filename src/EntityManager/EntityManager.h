#ifndef ENTITYMANAGER_H_INCLUDED
#define ENTITYMANAGER_H_INCLUDED

#include <map>
#include <string>
#include "../const.h"
#include "../Include/EntityInfo.h"
#include "SFML/Graphics.hpp"

enum class EntityName {
    SHEEP
};

enum class EntityType {
    ENEMY
};

typedef std::map< EntityType, std::map< EntityName, EntityInfo* > > EntityBox;

class EntityManager {
public:
    EntityManager();
    virtual ~EntityManager();

    EntityInfo* getEnemyInfo(EntityName name, EntityType type);
protected:
private:
    std::string getPath(EntityName name, EntityType type);

     EntityBox enemies;

    std::map< EntityName, std::string > ENTITY_NAME;
    std::map< EntityType, std::string > ENTITY_TYPE;
};


#endif // ENTITYMANAGER_H_INCLUDED
