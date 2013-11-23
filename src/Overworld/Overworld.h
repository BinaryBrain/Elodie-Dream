#ifndef OVERWORLD_H
#define OVERWORLD_H

#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "../Entity/Elodie.h"
#include "../JsonAccessor/JsonAccessor.h"
#include "../Game/GameView.h"

class Overworld {
public:
    Overworld();
    virtual ~Overworld();
    Elodie* getElodie();
    int moveUp();
    int moveDown();
    int moveRight();
    int moveLeft();
    void evolve();
    void drawOnView(GameView* view);

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
