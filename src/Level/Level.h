#ifndef LEVEL_H
#define LEVEL_H

#include <string>

#include "../const.h"
#include "../env.h"
#include "../Map/Mapper.h"
#include "../FileHandler/FileHandler.h"
#include "../Game/GameView.h"
#include "../EventHandler/EventHandler.h"
#include "../Displayable/Displayable.h"
#include "../TextureManager/TextureManager.h"

class Level : public Displayable {
public:
    Level(std::string filename, LevelEnv env, Elodie* elodie);
    virtual ~Level();

    void loadLevel(std::string filename, Elodie* elodie);
    void live(EventHandler* const& event, sf::Time animate);

    TileMap getTiles();
    EntityMap getEntities();

    void display(GameView* view);
    void setEnvironement(LevelEnv env);
    void applyEnv(TileMap tiles);

    void pause();
    void play(sf::Clock *frameClock);
protected:
private:
    TileMap tiles;
    EntityMap entities;
    LevelEnv environement;
    TextureManager* manager;
};

#endif // LEVEL_H
