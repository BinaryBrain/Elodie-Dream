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
    for(EntityBox::iterator it = enemies.begin(); it != enemies.end(); ++it) {
        for(std::map< EntityName, EntityInfo* >::iterator enemy = it->second.begin(); enemy != it->second.end(); ++enemy) {
            if(enemy->second) {
                delete enemy->second;
            }
        }
    }
}

EntityInfo* EntityManager::getEnemyInfo(EntityName name, EntityType type) {
    if(!enemies[type][name]) {

    }

    return enemies[type][name];
}

std::string EntityManager::getPath(EntityName name, EntityType type) {
    return ENTITIES_JSON_PATH+"/"+ENTITY_TYPE[type]+"/"+ENTITY_NAME[name]+".json";
}
