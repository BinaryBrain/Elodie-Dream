#ifndef LEVEL_H
#define LEVEL_H

#include <string>

#include "../Map/Mapper.h"
#include "../FileHandler/FileHandler.h"
#include "../Game/GameView.h"
#include "../EventHandler/EventHandler.h"
#include "../Displayable/Displayable.h"

class Level : public Displayable{
public:
    Level();
    Level(std::string filename, GameView* gameView);
    virtual ~Level();

    void loadLevel(std::string filename);
    void live(EventHandler* const& event, sf::Time animate);

    TileMap getTiles();
    EntityMap getEntities();

    void display(GameView* view);

    void pause();
    void play();
protected:
private:
    TileMap tiles;
    EntityMap entities;
};

#endif // LEVEL_H
