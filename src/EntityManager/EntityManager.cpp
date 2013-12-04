#include "EntityManager.h"

EntityManager::EntityManager() {
    ENTITY_NAME = {
        {EntityName::SHEEP, ENTITYNAME_SHEEP}
    };

    ENTITY_TYPE = {
        {EntityType::ENEMY, ENTITYTYPE_ENEMY}
    };
}

EntityManager::~EntityManager() {
    for(std::map< EntityName, EntityInfo* >::iterator it = enemies.begin(); it != enemies.end(); it++) {
        if(it->second) {
            delete it->second;
        }
    }
}

EntityInfo* EntityManager::getEnemyInfo(EntityName name, EntityType type) {
    if(!enemies[name]) {

    }

    return enemies[name];
}

std::string EntityManager::getPath(EntityName name, EntityType type) {
    return ENTITIES_JSON_PATH+"/"+ENTITY_TYPE[type]+"/"+ENTITY_NAME[name]+".json";
}
