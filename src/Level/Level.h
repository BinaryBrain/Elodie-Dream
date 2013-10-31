#ifndef LEVEL_H
#define LEVEL_H

#include <string>

#include "../Map/MapParser.h"
#include "../FileHandler/FileHandler.h"

class Level
{
    public:
        Level();
        virtual ~Level();

        void loadLevel(std::string filename);
    protected:
    private:
};

#endif // LEVEL_H
