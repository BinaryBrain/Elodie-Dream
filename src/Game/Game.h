#ifndef GAME_H
#define GAME_H

#include "../icon.h"
#include "../env.h"
#include "../Level/EndingScreen.h"
#include "../Level/Death.h"
#include "../Json/JsonStringifier.h"
#include "../FileHandler/ConfigManager.h"
#include "../FileHandler/SaveHandler.h"
#include "../Console/Console.h"
#include "../Level/Level.h"
#include "../Map/Mapper.h"
#include "../Overworld/Overworld.h"
#include "../EventHandler/EventHandler.h"
#include "../Menu/MenuHandler.h"
#include "../Fnu/Girly.h"
#include "../Level/Hud.h"
#include "../Sound/SoundManager.h"
#include "../Score/ScoreBoard.h"
#include "../Score/ScoreManager.h"
#include "../Stats/StatsBoard.h"
#include "../Stats/StatsManager.h"
#include "../Menu/TitleScreen.h"
#include "../Utils/Date.h"
#include "GameView.h"

class Level;
class Overworld;
class SoundManager;

/**
* The class representing the game.
* Uses the Singleton Pattern so that Game can be instantiated only one time. Thus, the constructor is private an
* getInstance can be used to get the only instance of Game.
*/
class Game
{
public:
    static Game& getInstance();

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
    void toggleMute(sf::Music& music);

private:
    Game();
    ~Game();

    Game(const Game&);
    Game& operator= (Game const&);

    std::vector<int> curLevelNbr = {0,0};
    bool autoSave = false;
    bool mute;
    bool showTutoConsole = false;
    bool showCastleConsole = false;

    GameView view;
    GameState state = GameState::INMENU;
    GameState pausePrevState;
    GameState defaultReturnState;

    Date now;
    sf::Clock frameClock;

    MenuComponent* currentMenuComponent;
    MenuComponent* currentMenuSave;
    MenuHandler menuHandler = MenuHandler(view);

    ConfigManager configManager;
    JsonAccessor jsonAccessor;
    SaveHandler& saveHandler;
    SoundManager& soundManager;
    ScoreManager& scoreManager;
    StatsManager& statsManager;

    TitleScreen* title = NULL;
    ScoreBoard scoreBoard = ScoreBoard(view);
    StatsBoard statsBoard = StatsBoard(view);
    Console console = Console(view);
    Girly girly = Girly(view);
    Hud hud = Hud(view);

    Overworld* overworld = NULL;
    Death* death = NULL;
    EndingScreen* endingScreen = NULL;
    Level* curLevel = NULL;

    EventHandler event = EventHandler(view.getWindow());


    void displayScore();
    void displayStats();
    void handleOverworld(sf::Time time);
    void displayMenu();
    void displayConsole();
    void displayLevel(sf::Time time);
    void loadLevel(std::vector<int> levelNbr);
    bool girlyMode = false;
    void dead();
    void displayEnd();
    void newGame();
    void leaveLevel();
    void animPrevOw();
    void animNextOw();

    bool owfadeIn = false;
    bool owfadeOut = false;
    bool moveout = false;
    //double miny = 200;
    //int totframe = 0;
    //double frametime = 0;
};

#endif // GAME_H
