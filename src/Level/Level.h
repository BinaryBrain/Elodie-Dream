#ifndef LEVEL_H
#define LEVEL_H

#include <string>

#include "../Map/Mapper.h"
#include "../FileHandler/FileHandler.h"

class Level
{
    public:
        Level();
        Level(std::string filename);
        virtual ~Level();

        void loadLevel(std::string filename);

        TileMap getTiles();
        EntitieVector getEntities();
    protected:
    private:
        TileMap tiles;
        EntitieVector entities;
};

#endif // LEVEL_H
