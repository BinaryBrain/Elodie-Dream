#include "EntityManager.h"

// Initialisation of the singleton to NULL
EntityManager* EntityManager::managerInstance = NULL;

EntityManager::EntityManager() {
    ENTITY_NAME = {
        {EntityName::ELODIE, ENTITYNAME_ELODIE},
        {EntityName::SHEEP, ENTITYNAME_SHEEP},
        {EntityName::MAGMACUBE, ENTITYNAME_MAGMACUBE},
        {EntityName::SPIKES, ENTITYNAME_SPIKES},
        {EntityName::PORTAL, ENTITYNAME_PORTAL}
    };

    ENTITY_TYPE = {
        {EntityType::ELODIE, ENTITYTYPE_ELODIE},
        {EntityType::ENEMY, ENTITYTYPE_ENEMY},
        {EntityType::MISC, ENTITYTYPE_MISC}
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

// Gets the instance of the entityManger
EntityManager* EntityManager::getInstance() {
    if(!managerInstance) managerInstance = new EntityManager();
    return managerInstance;
}

void EntityManager::kill() {
    if(managerInstance) {
        delete managerInstance;
        managerInstance = NULL;
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
