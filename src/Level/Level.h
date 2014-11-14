#ifndef LEVEL_H
#define LEVEL_H

#include <string>

#include "../const.h"
#include "../env.h"
#include "../Game/Game.h"
#include "../Map/Mapper.h"
#include "../FileHandler/FileHandler.h"
#include "../Game/GameView.h"
#include "../EventHandler/EventHandler.h"
#include "../Displayable/Displayable.h"
#include "../TextureManager/TextureManager.h"
#include "../Sky/Sky.h"
#include "../Sky/Earth.h"

class Game;
class Elodie;

class Level : public Displayable {
public:
    Level(GameView& gameView, std::string filename, LevelEnv env, Elodie& elodie);
    virtual ~Level();

    void loadLevel(std::string filename, Elodie& elodie);
    void live(const EventHandler& event, sf::Time animate);

    TileMap getTiles();
    EntityMap getEntities();

    void display();
    void setEnvironement(LevelEnv env);
    void applyEnv(TileMap tiles);

    void pause();
    void play(sf::Clock* frameClock);

    sf::Music& getMusic();
    bool isDead();
    bool isCleared();
    bool mustLeave();

private:
    std::pair <float,float> getSlowVariables(LevelEnv env);
    TileMap tiles;
    EntityMap entities;
    LevelEnv environement;
    TextureManager manager;
    sf::Music music;
    Sky* sky;
    Earth* earth;
};

#endif // LEVEL_H
