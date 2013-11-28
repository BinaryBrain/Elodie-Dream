#ifndef GAME_H
#define GAME_H

#include "../env.h"
#include "../Level/Level.h"
#include "../Map/Mapper.h"
#include "../FileHandler/FileHandler.h"
#include "../Overworld/Overworld.h"
#include "../EventHandler/EventHandler.h"
#include "../Menu/MenuHandler.h"
#include "GameView.h"


/**
* The class representing the game.
* Uses the Singleton Pattern so that Game can be instantiated only one time. Thus, the constructor is private an
* getInstance can be used to get the only instance of Game.
*/
class Game {
public:
    static Game* getInstance();
    static void kill();

    void init();
    void draw();
    void run();
    void exit();

    Level loadLevel(std::string filename);

    void setState(GameState state);

private:
    Game();
    ~Game();

    static Game* gameInstance;
    Game& operator= (Game const&); // Makes operator= private

    GameView view;

    GameState state = GameState::INMENU;

    EventHandler* event;

    Overworld* overworld;
    void handleOverworld();

    sf::Clock frameClock;

    MenuHandler* menuHandler;

    void displayMenu();

    int curLevelNbr = 0;
    Level* curLevel = NULL;
    void displayLevel(int curLevel);
    void loadLevel(int levelNbr);
};

#endif // GAME_H
