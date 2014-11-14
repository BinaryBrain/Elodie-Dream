#include "Portal.h"

const std::map< int, std::string > Portal::ANIMATIONS =
  {
    {Portal::State::STANDING, "standing"}
  };

Portal::Portal() : Portal(sf::Vector2f(0, 0))
{
}

Portal::Portal(sf::Vector2f position) :
  Entity(position, EntityType::MISC, EntityName::PORTAL,
	 ENTITYTYPE_MISC+"/"+ENTITYNAME_PORTAL+".png", "standing",
	 Portal::ANIMATIONS, Portal::State::STANDING, {0, 0}, 1)
{
}

Portal::Portal(float x, float y) : Portal(sf::Vector2f(x, y))
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
