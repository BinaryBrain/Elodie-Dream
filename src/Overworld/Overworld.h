#ifndef OVERWORLD_H
#define OVERWORLD_H

#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "../Entities/Elodie.h"
#include "../JsonAccessor/JsonAccessor.h"

class Overworld
{
    public:
        Overworld();
        virtual ~Overworld();
        sf::Sprite* getCurrentSprite();
        Elodie* getElodie();
        sf::VertexArray* getPath();
        int moveUp();
        int moveDown();
        int moveRight();
        int moveLeft();
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
        std::vector<sf::VertexArray*> paths;
        std::vector<std::vector<int>*> levelPos;

        size_t curPosInPath=0;

        Elodie* elodie;
};

#endif // OVERWORLD_H
