#ifndef OVERWORLD_H
#define OVERWORLD_H

#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

class Overworld
{
    public:
        Overworld();
        virtual ~Overworld();
        sf::Sprite* getCurrentSprite();
        void evolve();

    protected:
    private:
        enum states {
            UNIL = 0,
            CASTLE = 1,
            VOLCANO = 2,
            FRELJORD = 3
        };

        states currentState;
        std::vector<sf::Sprite*> overworldSprites;
};

#endif // OVERWORLD_H
