#ifndef ENTITIE_H
#define ENTITIE_H

#include <iostream>
#include <SFML/Graphics.hpp>

class Entity
{
    public:
        Entity();
        virtual ~Entity();

        virtual sf::Sprite* getSprite() = 0; // Make the class abstract
    protected:
    private:
        sf::Sprite* m_sprite;
};

#endif // ENTITIES_H
