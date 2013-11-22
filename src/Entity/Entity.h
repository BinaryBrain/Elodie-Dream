#ifndef ENTITIE_H
#define ENTITIE_H

#include <iostream>
#include <SFML/Graphics.hpp>

#include "../Sprite/TileSprite.h"
#include "../EventHandler/EventHandler.h"

/**
* The class representing entities.
*/
class Entity {
public:
    /**
    * \brief The constructor of Entity. Sets its sprite to be NULL.
    */
    Entity();
    /**
    * \brief The destructor of Entity.
    */
    virtual ~Entity();

    void addHitbox(std::tuple< sf::Vector2f, sf::Vector2f > hitbox);
    void setCurrentHitbox(int current);
    std::tuple< sf::Vector2f, sf::Vector2f > getCurrentHitbox();

    void updateHitboxes(sf::Vector2f speed);

    std::map<std::string, float> collideWithTiles(std::vector< std::vector<TileSprite*> > const& world);

    /**
    * \brief A getter to the main Sprite
    *
    * \return A pointer to the Sprite.
    */
    virtual sf::Sprite* getSprite() = 0;
    virtual void doStuff(EventHandler* const& event, std::vector< std::vector<TileSprite*> > const& tiles, sf::Time animate) = 0;
protected:
private:
    int checkTiles(std::vector< std::vector<TileSprite*> > const& world, int x, int y);
    sf::Sprite* sprite;
    std::vector< std::tuple< sf::Vector2f, sf::Vector2f > > hitboxes;
    int currentHitbox;
};

#endif // ENTITIES_H
