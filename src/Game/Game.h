#ifndef GAME_H
#define GAME_H

#include <string>

#include "../Level/Level.h"
#include "../Map/Mapper.h"
#include "../FileHandler/FileHandler.h"
#include "../Overworld/Overworld.h"
#include "../EventHandler/EventHandler.h"
#include "../Menu/Menu.h"
#include "GameView.h"

class Game {
public:
    Game();
    virtual ~Game();

    void init();
    void draw();
    void run();

    Level loadLevel(std::string filename);
protected:
private:
    EventHandler* event;

    Overworld overworld;
    sf::Clock frameClock;

    Menu menu;

    GameView view;

    bool inLevel = true;
};

#endif // GAME_H
