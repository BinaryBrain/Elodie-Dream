#include "Portal.h"

const std::map< int, std::string > Portal::ANIMATIONS =
{
    {Portal::State::STANDING, "standing"}
};

Portal::Portal() : Portal(sf::Vector2f(0, 0), ENTITYTYPE_MISC, ENTITYNAME_PORTAL, EntityType::MISC, EntityName::PORTAL)
{
}

Portal::Portal(sf::Vector2f position, std::string entityType, std::string entityName, EntityType type, EntityName name) :
    Entity(position, type, name,
           entityType+"/"+entityName+".png", "standing",
           Portal::ANIMATIONS, Portal::State::STANDING, {0, 0}, 1)
{
}

Portal::Portal(float x, float y, std::string entityType, std::string entityName, EntityType type, EntityName name) :
    Portal(sf::Vector2f(x, y), entityType, entityName, type, name)
{
}

Portal::~Portal()
{
}

void  Portal::takeDamage(int, bool)
{
}

void Portal::doStuff(const EventHandler&, const std::vector< std::vector<TileSprite*> >&,
                     std::map< std::string, Entity* >&, sf::Time animate)
{
    update(animate);
}
