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

    EventHandler* event = new EventHandler(view.getWindow());

    Overworld* overworld = new Overworld();
    void handleOverworld();

    sf::Clock frameClock;

    MenuHandler* menuHandler = new MenuHandler();
    void displayMenu();

    Console* console = new Console();

    // don't know which one to choose : Game.writeInConsole() of Game.getConsole.setContent()
    Console* getConsole();
    void writeInConsole(std::string sentence);
    void writeInConsole(std::vector<std::string> sentences);

    int curLevelNbr = 0;
    Level* curLevel = NULL;
    void displayLevel(int curLevel);
    void loadLevel(int levelNbr);

    Girly* girly = new Girly();
    bool girlyMode = false;
};

#endif // GAME_H
