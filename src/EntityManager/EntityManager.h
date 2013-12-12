#ifndef ENTITYMANAGER_H_INCLUDED
#define ENTITYMANAGER_H_INCLUDED

#include <map>
#include <string>
#include "../const.h"
#include "../Include/EntityInfo.h"
#include "SFML/Graphics.hpp"
#include "../Json/JsonParser.h"
#include "../Json/JsonAccessor.h"

enum class EntityName {
    ELODIE, SHEEP, MAGMACUBE, SPIKES, GHOST, PORTAL
};

enum class EntityType {
    ELODIE, ENEMY, MISC
};

typedef std::map< EntityType, std::map< EntityName, EntityInfo* > > EntityBox;

class EntityManager {
public:
    static EntityManager* getInstance();
    static void kill();
    EntityInfo* getEnemyInfo(EntityType type, EntityName name);
protected:
private:
    EntityManager();
    virtual ~EntityManager();

    static EntityManager* managerInstance;
    EntityManager& operator= (EntityManager const&); // Makes operator= private

    std::string getPath(EntityType type, EntityName name);

     EntityBox enemies;

    std::map< EntityName, std::string > ENTITY_NAME;
    std::map< EntityType, std::string > ENTITY_TYPE;
};


#endif // ENTITYMANAGER_H_INCLUDED
