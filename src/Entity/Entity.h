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
    * \brief Used to make the class abstract.
    *
    * \return 0: there isn't any sprite to get because Entity is abstract.
    */
    virtual sf::Sprite* getSprite() = 0;
protected:
private:
    sf::Sprite* m_sprite;
};

#endif // ENTITIES_H
