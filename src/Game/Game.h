#ifndef GAME_H
#define GAME_H

#include "../env.h"
#include "../JsonAccessor/JsonAccessor.h"
#include "../Console/Console.h"
#include "../Level/Level.h"
#include "../Map/Mapper.h"
#include "../FileHandler/FileHandler.h"
#include "../Overworld/Overworld.h"
#include "../EventHandler/EventHandler.h"
#include "../Menu/MenuHandler.h"
#include "../Fnu/Girly.h"
#include "../Level/Immersionbar.h"
#include "../Sound/SoundManager.h"
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

    void draw();
    void run();
    void exit();

    void setState(GameState state);
    Overworld* getOverworld();
    Console* getConsole();

private:
    Game();
    ~Game();

    static Game* gameInstance;
    Game& operator= (Game const&); // Makes operator= private

    GameView view;
    GameState state = GameState::INMENU;
    GameState pausePrevState;

    EventHandler* event = new EventHandler(view.getWindow());

    Overworld* overworld = new Overworld();
    void handleOverworld(sf::Time time);

    sf::Clock frameClock;

    MenuHandler* menuHandler = new MenuHandler();
    void displayMenu();

    Console* console;
    void displayConsole();

    void writeInConsole(std::string sentence);
    void writeInConsole(std::vector<std::string> sentences);

    int curLevelNbr = 0;
    Level* curLevel = NULL;
    void displayLevel(int curLevel, sf::Time time);
    void loadLevel(int levelNbr);

    Girly* girly = new Girly();
    bool girlyMode = false;

    ImmersionBar* immBar = new ImmersionBar();
};

#endif // GAME_H
