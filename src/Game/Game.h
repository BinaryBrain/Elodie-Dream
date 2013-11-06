#ifndef GAME_H
#define GAME_H

#include <string>

#include "../Level/Level.h"
#include "../Map/Mapper.h"
#include "../FileHandler/FileHandler.h"
#include "../Overworld/Overworld.h"

class Game
{
    public:
        Game();
        virtual ~Game();

        void init();
        void draw();

        void loadLevel(std::string filename);
    protected:
    private:
        sf::RenderWindow* window;
        Overworld overworld;
        sf::Clock frameClock;
};

#endif // GAME_H
