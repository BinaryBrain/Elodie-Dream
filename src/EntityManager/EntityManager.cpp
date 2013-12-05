#include "EntityManager.h"
#include "../Json/JsonParser.h"
#include "../Json/JsonAccessor.h"

EntityManager::EntityManager() {
    ENTITY_NAME = {
        {EntityName::ELODIE, ENTITYNAME_ELODIE},
        {EntityName::SHEEP, ENTITYNAME_SHEEP}
    };

    ENTITY_TYPE = {
        {EntityType::ELODIE, ENTITYTYPE_ELODIE},
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

EntityInfo* EntityManager::getEnemyInfo(EntityType type, EntityName name) {
    if(!enemies[type][name]) {
        JsonAccessor newEntity = JsonAccessor();
        newEntity.load(getPath(type, name));
        enemies[type][name] = newEntity.getEntityInfo();
    }

    return enemies[type][name];
}

std::string EntityManager::getPath(EntityType type, EntityName name) {
    return ENTITIES_JSON_PATH+"/"+ENTITY_TYPE[type]+"/"+ENTITY_NAME[name]+".json";
}
