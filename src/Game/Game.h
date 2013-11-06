#ifndef GAME_H
#define GAME_H

#include <string>

#include "../Level/Level.h"
#include "../Map/MapParser.h"
#include "../FileHandler/FileHandler.h"
#include "../Overworld/Overworld.h"

class Game
{
    public:
        Game();
        virtual ~Game();

        void init();
        void draw();

        Level loadLevel(std::string filename);
    protected:
    private:
        sf::RenderWindow* window;
        Overworld overworld;
        sf::Clock frameClock;
};

#endif // GAME_H
