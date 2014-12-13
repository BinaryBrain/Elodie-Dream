#include "EntityManager.h"

EntityManager::EntityManager()
{
    ENTITY_NAME =
    {
        {EntityName::ELODIE, ENTITYNAME_ELODIE},
        {EntityName::SHEEP, ENTITYNAME_SHEEP},
        {EntityName::MAGMACUBE, ENTITYNAME_MAGMACUBE},
        {EntityName::BRISTLE, ENTITYNAME_BRISTLE},
        {EntityName::GHOST, ENTITYNAME_GHOST},
        {EntityName::SPIKES, ENTITYNAME_SPIKES},
        {EntityName::METEORITE, ENTITYNAME_METEORITE},
        {EntityName::PORTAL, ENTITYNAME_PORTAL},
        {EntityName::PORO, ENTITYNAME_PORO},
        {EntityName::SPRITE, ENTITYNAME_SPRITE}
    };

    ENTITY_TYPE =
    {
        {EntityType::ELODIE, ENTITYTYPE_ELODIE},
        {EntityType::ENEMY, ENTITYTYPE_ENEMY},
        {EntityType::MISC, ENTITYTYPE_MISC},
        {EntityType::BONUS, ENTITYTYPE_BONUS}
    };
}

EntityManager::~EntityManager()
{
    for(EntityBox::iterator it = enemies.begin(); it != enemies.end(); ++it)
    {
        for(std::map< EntityName, EntityInfo* >::iterator enemy = it->second.begin(); enemy != it->second.end(); ++enemy)
        {
            if(enemy->second)
            {
                delete enemy->second;
            }
        }
    }
}

// Gets the instance of the entityManger
EntityManager& EntityManager::getInstance()
{
    static EntityManager instance;
    return instance;
}

EntityInfo* EntityManager::getEnemyInfo(EntityType type, EntityName name)
{
    if(!enemies[type][name])
    {
        JsonAccessor newEntity = JsonAccessor();
        newEntity.loadJsonFrom(getPath(type, name));
        enemies[type][name] = newEntity.getEntityInfo();
    }

    return enemies[type][name];
}

std::string EntityManager::getPath(EntityType type, EntityName name)
{
    return ENTITIES_JSON_PATH+"/"+ENTITY_TYPE[type]+"/"+ENTITY_NAME[name]+".json";
}
