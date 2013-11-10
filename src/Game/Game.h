#ifndef GAME_H
#define GAME_H

#include <string>

#include "../Level/Level.h"
#include "../Map/Mapper.h"
#include "../FileHandler/FileHandler.h"
#include "../Overworld/Overworld.h"
#include "../EventHandler/EventHandler.h"
#include "GameView.h"

class Game
{
    public:
        Game();
        virtual ~Game();

        void init();
        void draw();
        void run();

        Level loadLevel(std::string filename);
    protected:
    private:
        EventHandler* event;

        Overworld overworld;
        sf::Clock frameClock;

        GameView view;

        float toMove = 0;
        float speed = 0.3;
        bool goingUp = false;
        bool goingDown = false;
        bool goingRight = false;
        bool goingLeft = false;
        bool isMoving();
        void noMoves();
};

#endif // GAME_H
