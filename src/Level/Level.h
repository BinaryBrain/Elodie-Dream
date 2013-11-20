#ifndef LEVEL_H
#define LEVEL_H

#include <string>

#include "../Map/Mapper.h"
#include "../FileHandler/FileHandler.h"
#include "../Game/GameView.h"

class Level {
public:
    Level();
    Level(std::string filename);
    virtual ~Level();

    void loadLevel(std::string filename);

    TileMap getTiles();
    EntityMap getEntities();

    void draw(GameView* view);
protected:
private:
    TileMap tiles;
    EntityMap entities;
};

#endif // LEVEL_H
