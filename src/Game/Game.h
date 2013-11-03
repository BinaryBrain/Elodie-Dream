#ifndef GAME_H
#define GAME_H

#include <string>

#include "../Level/Level.h"
#include "../Map/MapParser.h"
#include "../FileHandler/FileHandler.h"

class Game
{
    public:
        Game();
        virtual ~Game();

        Level loadLevel(std::string filename);
    protected:
    private:
};

#endif // GAME_H

