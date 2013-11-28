#ifndef ENTITIE_H
#define ENTITIE_H

#include <iostream>
#include <SFML/Graphics.hpp>

#include "../Sprite/TileSprite.h"
#include "../EventHandler/EventHandler.h"
#include "Hitbox.h"

/**
* The class representing entities.
*/
class Entity {
public:
    /**
    * \brief The constructor of Entity. Sets its sprite to be NULL.
    */
    Entity();

    Entity(sf::Sprite* sprite);
    /**
    * \brief The destructor of Entity.
    */
    virtual ~Entity();

    void addHitbox(Hitbox hitbox);
    void setCurrentHitbox(int current);
    Hitbox getCurrentHitbox();

    std::map<std::string, float> collideWithTiles(std::vector< std::vector<TileSprite*> > const& world);

    /**
    * \brief A getter to the main Sprite
    *
    * \return A pointer to the Sprite.
    */
    virtual sf::Sprite* getSprite() = 0;

    void setEntitySprite(sf::Sprite* sprite);

    virtual void doStuff(EventHandler* const& event, std::vector< std::vector<TileSprite*> > const& tiles, sf::Time animate) = 0;

    void computeGravity();
    void move(sf::Vector2f& diff);
    void move(float dx, float dy);
protected:
    sf::Sprite* sprite;
    sf::Vector2f speed;

private:
    int checkTiles(std::vector< std::vector<TileSprite*> > const& world, int x, int y);
    std::vector< Hitbox > hitboxes;
    int currentHitbox;
};

#endif // ENTITIES_H
