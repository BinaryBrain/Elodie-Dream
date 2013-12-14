#ifndef GAME_H
#define GAME_H

#include "../icon.h"
#include "../env.h"
#include <windows.h>
#include "../Level/EndingScreen.h"
#include "../Level/Death.h"
#include "../Json/JsonStringifier.h"
#include "../FileHandler/SaveHandler.h"
#include "../Console/Console.h"
#include "../Level/Level.h"
#include "../Map/Mapper.h"
#include "../Overworld/Overworld.h"
#include "../EventHandler/EventHandler.h"
#include "../Menu/MenuHandler.h"
#include "../Fnu/Girly.h"
#include "../Level/Immersionbar.h"
#include "../Sound/SoundManager.h"
#include "../Score/Scoreboard.h"
#include "../Score/ScoreManager.h"
#include "../Menu/TitleScreen.h"
#include "GameView.h"

class Level;
class Overworld;
class Death;
class Scoreboard;
class SoundManager;
class EndingScreen;

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
    void load();
    void save();
    void exit();

    GameState getState();
    void setState(GameState state);
    Overworld* getOverworld();
    Console* getConsole();

    bool isMute();
    void toggleMute();
private:
    Game();
    ~Game();

    static Game* gameInstance;
    Game& operator= (Game const&);

    GameView view;
    GameState state = GameState::INMENU;
    MenuComponent* currentMenuItem;

    GameState pausePrevState;

    SoundManager* soundManager;

    ScoreManager* scoreManager;

    Scoreboard* scoreboard = NULL;
    void displayScore();

    EventHandler* event = NULL;
    Overworld* overworld = NULL;

    void handleOverworld(sf::Time time);

    sf::Clock frameClock;

    MenuHandler* menuHandler;
    void displayMenu();

    Console* console = NULL;
    void displayConsole();

    int curLevelNbr = 0;
    Level* curLevel = NULL;
    void displayLevel(int curLevel, sf::Time time);
    void loadLevel(int levelNbr);

    Girly* girly = NULL;
    bool girlyMode = false;

    bool mute;

    ImmersionBar* immBar = NULL;

    Death* death = NULL;
    void dead();

    EndingScreen* endingScreen = NULL;
    void displayEnd();

    void newGame();
    GameState defaultReturnState;
    void leaveLevel();
    TitleScreen* title = NULL;
    bool showTutoConsole = false;
    bool showCastleConsole = false;
};

#endif // GAME_H
