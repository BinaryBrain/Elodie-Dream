#ifndef ENTITIE_H
#define ENTITIE_H

#include <iostream>
#include <SFML/Graphics.hpp>

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

    /**
    * \brief A getter to the main Sprite
    *
    * \return A pointer to the Sprite.
    */
    virtual sf::Sprite* getSprite() = 0;
protected:
private:
    sf::Sprite* sprite;
};

#endif // ENTITIES_H
