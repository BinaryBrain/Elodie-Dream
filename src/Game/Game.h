#ifndef GAME_H
#define GAME_H

#include <string>

#include "../Level/Level.h"
#include "../Map/Mapper.h"
#include "../FileHandler/FileHandler.h"
#include "../Overworld/Overworld.h"
#include "../EventHandler/EventHandler.h"

class Game
{
    public:
        Game();
        virtual ~Game();

        void init();
        void draw();
        void run();

        void loadLevel(std::string filename);
    protected:
    private:
        sf::RenderWindow* window;
        EventHandler* event;
        Overworld overworld;
        sf::Clock frameClock;
};

#endif // GAME_H
