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

enum class GameState {
    INLEVEL, INOVERWORLD, INMENU
};

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
    GameState state = GameState::INMENU;

    EventHandler* event;

    Overworld overworld;
    void displayOverworld();

    sf::Clock frameClock;

    Menu menu;
    void displayMenu();

    GameView view;

    int curLevelNbr = 0;
    Level* curLevel;
    void displayLevel(int curLevel);
    void loadLevel(int levelNbr);
};

#endif // GAME_H
