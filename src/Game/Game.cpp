#include "Game.h"

Game::Game() :
    saveHandler(SaveHandler::getInstance()),
    soundManager(SoundManager::getInstance()),
    scoreManager(ScoreManager::getInstance()),
    statsManager(StatsManager::getInstance())
{
    configManager.load(SETTINGS_PATH + "/settings.json");

    mute = DEFAULT_MUTE;

    title = new TitleScreen(view);
    overworld = new Overworld(view, DEFAULT_MUTE);

    menuHandler.setInLevel(false);
    view.show(ViewLayer::TITLESCREEN);
}

Game::~Game()
{
    if (title)
    {
        delete title;
    }
    if (overworld)
    {
        delete overworld;
    }
}

// Gets the instance of the game
Game& Game::getInstance()
{
    static Game instance;
    return instance;
}

void Game::leaveLevel()
{
    state = GameState::INOVERWORLD;
    view.hide(ViewLayer::SKY);
    view.hide(ViewLayer::EARTH);
    view.hide(ViewLayer::LEVEL);
    view.hide(ViewLayer::HUD);
    view.hide(ViewLayer::CONSOLE);
    view.show(ViewLayer::OVERWORLD);
    if (!isMute() && overworld->getMusic().getStatus() != sf::Music::Status::Playing)
    {
        overworld->getMusic().play();
    }
    overworld->getElodie().stand();
    overworld->resetPos();

    if (curLevel)
    {
        delete curLevel;
        curLevel = NULL;
    }
    scoreManager.resetCurrentScore();
    menuHandler.getTitleMenu()->toNormalMenu();
}

void Game::displayLevel(int curLevelNbr, sf::Time time)
{
    //double ypos = ((Elodie*)curLevel->getEntities()["elodie"])->getPosition().y;
    //if (  ypos < miny) {
    //    miny = ypos;
    //}
    if (showTutoConsole || showCastleConsole)
    {
        std::string key;
        if (showTutoConsole)
        {
            key = "tutorial";
            showTutoConsole = false;
        }
        else if (showCastleConsole)
        {
            key = "castle";
            showCastleConsole = false;
        }
        jsonAccessor.loadJsonFrom(LANGUAGES_PATH + "/" + configManager.getLanguage() + ".lang");
        if (jsonAccessor.canTakeElementFrom(key))
        {
            curLevel->pause();
            state = GameState::INCONSOLE;
            view.show(ViewLayer::CONSOLE);
            console.clearAndWrite(jsonAccessor.getString(key));
            console.setNextState(GameState::INLEVEL);
        }
        showTutoConsole = false;

    }
    // leave level
    if (event.keyIsPressed(sf::Keyboard::Escape))
    {
        defaultReturnState = state;
        state = GameState::INMENU;
        curLevel->pause();
        menuHandler.setNextState(GameState::INLEVEL);
        menuHandler.resetMenu();
        menuHandler.setInLevel(true);
        view.show(ViewLayer::MENU);
        // toggle sound
    }
    else if(event.keyIsPressed(sf::Keyboard::M))
    {
        toggleMute(curLevel->getMusic());

        // the level
    }
    else
    {
        curLevel->live(event, time);
        hud.setLevel(((Elodie*)curLevel->getEntities()["elodie"])->getImmersionLevel());
        hud.setScore(scoreManager.getLevelPoints());

        // level leaving
        if (curLevel->mustLeave())
        {
            // level cleared
            if (curLevel->isCleared())
            {
                scoreManager.setLevel(curLevelNbr);
                scoreManager.computeTotalPoints();
                scoreManager.saveCurrentScore();
                scoreBoard.prepareText();
                scoreManager.resetCurrentScore();

                view.show(ViewLayer::SCORE);
                state = GameState::INSCORE;

                // death
            }
            else if (curLevel->isDead() && !GOD_MODE)
            {
                statsManager.setTotalDeaths(statsManager.getTotalDeaths() + 1);
                death = new Death(view, mute);
                view.show(ViewLayer::DEATH);
                state = GameState::DEAD;
            }
            curLevel->getMusic().stop();
        }
    }
}

void Game::loadLevel(int levelNbr)
{
    state = GameState::INLEVEL;
    curLevelNbr = levelNbr;
    LevelEnv env = LevelEnv::FIELD;
    switch (levelNbr)
    {
    case 0:
        showTutoConsole = true;
        env = LevelEnv::FIELD;
        break;
    case 1:
        env = LevelEnv::FIELD;
        break;
    case 2:
        env = LevelEnv::CASTLE;
        break;
    case 3:
        showCastleConsole = true;
        env = LevelEnv::CASTLE;
        break;
    case 4:
        env = LevelEnv::VOLCANO;
        break;
    case 5:
        env = LevelEnv::VOLCANO;
        break;
    case 6:
        env = LevelEnv::FRELJORD;
        break;
    case 7:
        env = LevelEnv::FRELJORD;
        break;
    default:
        env = LevelEnv::FIELD;
        break;
    }
    curLevel = new Level(view, "assets/levels/level"+Utils::itos(curLevelNbr)+".txt", env, overworld->getElodie());
    menuHandler.getTitleMenu()->toLevelMenu();
}

void Game::handleOverworld(sf::Time time)
{
    Elodie& elo = overworld->getElodie();

    if (elo.isMoving())
    {
        elo.overworldMove(time.asSeconds());
    }
    else if (event.keyIsHold(sf::Keyboard::Down))
    {
        elo.setDistanceToMove(overworld->moveDown());
        if (elo.hasToMove())
        {
            elo.setWalkDown();
        }
    }
    else if (event.keyIsHold(sf::Keyboard::Up))
    {
        elo.setDistanceToMove(overworld->moveUp());
        if (elo.hasToMove())
        {
            elo.setWalkUp();
        }
    }
    else if (event.keyIsHold(sf::Keyboard::Left))
    {
        elo.setDistanceToMove(overworld->moveLeft());
        if (elo.hasToMove())
        {
            elo.setWalkLeft();
        }
    }
    else if (event.keyIsHold(sf::Keyboard::Right))
    {
        elo.setDistanceToMove(overworld->moveRight());
        if (elo.hasToMove())
        {
            elo.setWalkRight();
        }
    }
    else if (event.keyIsPressed(sf::Keyboard::Return) || event.keyIsPressed(sf::Keyboard::Space))
    {
        if (overworld->getLevelToLoad() >= 0)
        {
            loadLevel(overworld->getLevelToLoad());
            view.hide(ViewLayer::OVERWORLD);
            overworld->getMusic().stop();
            view.show(ViewLayer::SKY);
            view.show(ViewLayer::EARTH);
            view.show(ViewLayer::LEVEL);
            view.show(ViewLayer::HUD);
        }
    }
    else if (event.keyIsPressed(sf::Keyboard::Escape))
    {
        menuHandler.resetMenu();
        defaultReturnState = state;
        state = GameState::INMENU;
        menuHandler.setNextState(GameState::INOVERWORLD);
        view.show(ViewLayer::MENU);
        menuHandler.setInLevel(false);
        // testing purposes
    }
    else if (event.keyIsPressed(sf::Keyboard::M))
    {
        toggleMute(overworld->getMusic());
        // testing purposes
    }
    elo.update(time);
}

void Game::displayMenu()
{
    if (event.keyIsPressed(sf::Keyboard::Down))
    {
        menuHandler.incIndex();
    }
    if (event.keyIsPressed(sf::Keyboard::Up))
    {
        menuHandler.decIndex();
    }
    if (event.keyIsPressed(sf::Keyboard::Return))
    {
        currentMenuComponent = menuHandler.getCurrentMenuComponent();
        state = currentMenuComponent->getState();

        if (state == GameState::INOVERWORLD)
        {
            view.hide(ViewLayer::MENU);
            view.hide(ViewLayer::TITLESCREEN);
            leaveLevel();
            overworld->getElodie().play();

        }
        else if (state == GameState::INLEVEL)
        {
            if (curLevel)
            {
                view.hide(ViewLayer::MENU);
                view.show(ViewLayer::LEVEL);
                view.show(ViewLayer::HUD);
                state = GameState::INLEVEL;
                curLevel->play(&frameClock);
            }
            else
            {
                std::cerr << "Must display level but not initialized." << std::endl;
            }

        }
        else if (state == GameState::SAVE)
        {
            // sets the current slot and name
            autoSave = true;
            currentMenuSave = currentMenuComponent;
        }
        else if (state == GameState::INSTATS)
        {
            statsBoard.prepareText();
            view.hide(ViewLayer::MENU);
            view.show(ViewLayer::STATS);
        }

    }
    else if (event.keyIsPressed(sf::Keyboard::Escape))
    {
        defaultReturnState = state;
        state = menuHandler.getNextState();
        if (state == GameState::INOVERWORLD)
        {
            view.hide(ViewLayer::MENU);
            view.show(ViewLayer::OVERWORLD);
            overworld->getElodie().stand();
            overworld->resetPos();
            if (curLevel)
            {
                delete curLevel;
                curLevel = NULL;
            }
        }
        else if (state == GameState::INLEVEL)
        {
            if (curLevel)
            {
                state = GameState::INLEVEL;
                view.hide(ViewLayer::MENU);
                view.show(ViewLayer::LEVEL);
                view.show(ViewLayer::HUD);
                curLevel->play(&frameClock);
            }
            else
            {
                std::cerr << "Must display level but not initialized." << std::endl;
            }
        }
    }
    else if (event.keyIsPressed(sf::Keyboard::M))
    {
        toggleMute(overworld->getMusic());
    }
}

void Game::displayConsole()
{
    if (event.keyIsPressed(sf::Keyboard::Up))
    {
        console.previousPage();
    }
    if (event.keyIsPressed(sf::Keyboard::Down))
    {
        console.nextPage();
    }
    if (event.keyIsPressed(sf::Keyboard::Space) || event.keyIsPressed(sf::Keyboard::Return))
    {
        state = console.getNextState();
        if (state == GameState::INOVERWORLD)
        {
            view.hide(ViewLayer::CONSOLE);
            view.hide(ViewLayer::MENU);
            view.show(ViewLayer::OVERWORLD);
            view.hide(ViewLayer::TITLESCREEN);
        }
        else if (state == GameState::INLEVEL)
        {
            if (curLevel)
            {
                state = GameState::INLEVEL;
                view.hide(ViewLayer::CONSOLE);
                view.show(ViewLayer::LEVEL);
                curLevel->play(&frameClock);
            }
            else
            {
                std::cerr << "Must display level but not initialized." << std::endl;
            }
        }
        else if (state == GameState::INMENU)
        {
            view.hide(ViewLayer::CONSOLE);
            view.show(ViewLayer::MENU);
        }
    }
}

void Game::dead()
{
    if (event.keyIsPressed(sf::Keyboard::Return) || event.keyIsPressed(sf::Keyboard::Space) )
    {
        view.hide(ViewLayer::DEATH);
        if (death)
        {
            delete death;
            death = NULL;
        }
        leaveLevel();
    }
    else if (event.keyIsPressed(sf::Keyboard::M))
    {
        toggleMute(death->getMusic());
    }
}

void Game::displayEnd()
{
    if (event.keyIsPressed(sf::Keyboard::Return) || event.keyIsPressed(sf::Keyboard::Space))
    {
        view.hide(ViewLayer::ENDINGSCREEN);
        if (endingScreen)
        {
            delete endingScreen;
            endingScreen = NULL;
        }
        leaveLevel();
        if (autoSave)
        {
            save();
        }
    }
    else if (event.keyIsPressed(sf::Keyboard::M))
    {
        toggleMute(endingScreen->getMusic());
    }
}

void Game::displayScore()
{
    if (event.keyIsPressed(sf::Keyboard::Return) || event.keyIsPressed(sf::Keyboard::Space))
    {
        view.hide(ViewLayer::SCORE);

        // end of game
        if (curLevelNbr == (NUMLEVELS-1))
        {
            endingScreen = new EndingScreen(view, mute);
            view.show(ViewLayer::ENDINGSCREEN);
            state = GameState::ENDINGSCREEN;
        }
        else
        {
            overworld->evolve(overworld->getState()[1], curLevelNbr + 1);
            overworld->setToLevel(curLevelNbr + 1);
            statsBoard.setLDL(overworld->getState()[1]);
            leaveLevel();
            if (autoSave)
            {
                save();
            }
        }
    }
}

void Game::displayStats()
{
    if (event.keyIsPressed(sf::Keyboard::Return) || event.keyIsPressed(sf::Keyboard::Escape))
    {
        view.hide(ViewLayer::STATS);
        view.show(ViewLayer::MENU);
        state = GameState::INMENU;
    }
}

void Game::run()
{
    sf::RenderWindow& window = view.getWindow();
    view.show(ViewLayer::MENU);

    window.setFramerateLimit(FPS);
    window.setIcon(icon.width, icon.height, icon.pixel_data);

    while (window.isOpen())
    {
        sf::Time sfTime = sf::seconds(1.0/FPS);//frameClock.restart();
        //if (sfTime.asSeconds() > MAX_TIME_FRAME)
        //    sfTime = sf::seconds(MAX_TIME_FRAME);
        //std::cout << 1.0/sfTime.asSeconds() << std::endl;
        //totframe++;
        //frametime += sfTime.asSeconds();
        event.listening();

        if (event.lostFocus())
        {
            if (curLevel)
            {
                pausePrevState = state;
                state = GameState::PAUSE;
                curLevel->pause();
            }
        }

        if (event.gainedFocus())
        {
            if (curLevel)
            {
                state = pausePrevState;
                curLevel->play(&frameClock);
            }
        }

        if (event.keyIsPressed(sf::Keyboard::F12))
        {
            sf::Image screen = window.capture();
            now.refreshTime();

            std::string date = now.getDMY("-") + "_" + now.getHMS("-");
            std::string screensDirPath = "screenshots";

            FileHandler::createDirIfNotExisting(screensDirPath);
            screen.saveToFile(screensDirPath+"/"+date+".jpg");
        }

        if (event.keyIsPressed(sf::Keyboard::G))
        {
            girlyMode = !girlyMode;
        }

        switch(state)
        {
        case GameState::INLEVEL:
            displayLevel(curLevelNbr, sfTime);
            break;
        case GameState::INOVERWORLD:
            handleOverworld(sfTime);
            break;
        case GameState::INMENU:
            displayMenu();
            break;
        case GameState::INCONSOLE:
            displayConsole();
            break;
        case GameState::PAUSE:
            break;
        case GameState::LOAD:
            load();
            break;
        case GameState::SAVE:
            save();
            break;
        case GameState::EXIT:
            exit();
            break;
        case GameState::DEAD:
            dead();
            break;
        case GameState::NEWGAME:
            newGame();
            break;
        case GameState::ENDINGSCREEN:
            displayEnd();
            break;
        case GameState::INSCORE:
            displayScore();
            break;
        case GameState::INSTATS:
            displayStats();
            break;
        default :
            std::cerr << "Error: unknown state" << std::endl;
            break;
        }


        view.hide(ViewLayer::GIRLY);
        if (girlyMode)
        {
            view.show(ViewLayer::GIRLY);
        }

        view.draw();
    }

    //double result = frametime/totframe;

    //std::cout << "Res :" << miny << std::endl;
    //char hihi;
    //std::cin >> hihi;
}

void Game::newGame()
{
    if (curLevel)
    {
        leaveLevel();
    }
    if (overworld)
    {
        delete overworld;
        overworld = NULL;
    }
    overworld = new Overworld(view, mute);
    view.addView(ViewLayer::OVERWORLD, overworld);
    state = GameState::INOVERWORLD;
    view.hide(ViewLayer::MENU);
    view.show(ViewLayer::OVERWORLD);
    view.hide(ViewLayer::TITLESCREEN);
    scoreManager.resetAllScores();
    statsManager.reset();
    statsBoard.setLDL(0);
    menuHandler.getTitleMenu()->toNormalMenu();

    // if there is a free slot, save on it
    std::string nextFreeSlot = saveHandler.nextFreeSlot();

    if (nextFreeSlot != "")
    {
        currentMenuSave = menuHandler.getMenuComponentFromKey(nextFreeSlot);
        save();
        autoSave = true;
    }
    else
    {
        autoSave = false;
    }
}

void Game::load()
{
    std::string path = "save/" + currentMenuComponent->getLabel() + ".save";
    std::string tempJsonFilePath = "save/temp.json";

    if (FileHandler::fileExists(path))
    {
        // resets the scores
        scoreManager.resetAllScores();
        statsManager.reset();

        // Sets the slot and text (for example for the autosave)
        autoSave = true;
        currentMenuSave = currentMenuComponent;

        // retrieves the saved values
        JsonAccessor accessor;
        bool jsonOk = accessor.setJson(saveHandler.getDecryptedContentFrom(path));
        std::cout << accessor.getCurrentJson() << std::endl;

        // if the save is valid
        if (jsonOk && accessor.canTakeElementFrom(SaveHandler::DATE_KEY) && accessor.canTakeElementFrom(SaveHandler::LDL_KEY))
        {
            std::string date = accessor.getString(SaveHandler::DATE_KEY);
            std::vector<int> LDL = {0,0};

            // if the version number exists
            if (accessor.canTakeElementFrom(SaveHandler::VERSION_KEY))
            {
                LDL = accessor.getIntVector(SaveHandler::LDL_KEY);

                if (accessor.canTakeElementFrom(SaveHandler::SCORES_KEY))
                {
                    std::vector< std::map<std::string, int> > datas = accessor.getVectMaps(SaveHandler::SCORES_KEY, scoreManager.getAllKeys());
                    scoreManager.setAllDatas(datas);
                }

                if (accessor.canTakeElementFrom(SaveHandler::MORESTATS_KEY))
                {
                    std::map<std::string, int> datas = accessor.getMap(SaveHandler::MORESTATS_KEY, statsManager.getAllKeys());
                    statsManager.setAllDatas(datas);
                }
            }
            else
            {
                 // save from version prior to 1.1
                 LDL[1] = accessor.getInt(SaveHandler::LDL_KEY);
            }


            if (curLevel)
            {
                leaveLevel();
            }
            if (!overworld)
            {
                overworld = new Overworld(view, mute);
                view.addView(ViewLayer::OVERWORLD, overworld);
            }
            overworld->setState(LDL[1]); // todo
            overworld->setToLevel(LDL[1]); // todo
            overworld->resetPos();
            overworld->getElodie().play();

            statsBoard.setLDL(LDL[1]); // todo

            console.clearAndWrite("Successfully loaded " + currentMenuComponent->getLabel() + ", from " + date + ".");
            console.setNextState(GameState::INOVERWORLD);

            menuHandler.getTitleMenu()->toNormalMenu();

        }
        else
        {
            console.clearAndWrite("Save corrupted.");
            console.setNextState(GameState::INMENU);
        }

    }
    else
    {
        console.clearAndWrite("Save doesn't exist.");
        console.setNextState(GameState::INMENU);
    }

    state = GameState::INCONSOLE;
    view.show(ViewLayer::MENU);
    view.show(ViewLayer::CONSOLE);
}

void Game::save()
{

    // creates date
    now.refreshTime();
    std::string date = "the " + now.getDMY("/") + ", at " + now.getHMS(":");

    // creates save with current slot and name
    std::string path = "save/" + currentMenuSave->getLabel() + ".save";

    std::vector<int> LDL = overworld->getState();

    // Displays the save name on the menu
    currentMenuSave->getText()->setString(saveHandler.computeLevelName(LDL[1])); // todo

    std::vector< std::map<std::string, int> > scoresDatas = scoreManager.getAllDatas();
    std::map<std::string, int> moreStatsDatas = statsManager.getAllDatas();

    // saves the datas to the save file
    JsonStringifier& stringifier = saveHandler.getStringifier();
    stringifier.add(SaveHandler::VERSION_KEY, GAME_VERSION);
    stringifier.add(SaveHandler::DATE_KEY, date);
    stringifier.add(SaveHandler::LDL_KEY, LDL);
    stringifier.add(SaveHandler::SCORES_KEY, scoresDatas);
    stringifier.add(SaveHandler::MORESTATS_KEY, moreStatsDatas);

    saveHandler.saveEncryptedContentTo(path);
    saveHandler.clearStringifier();

    // console confirmation
    // save() called from the menu
    if (state == GameState::SAVE)
    {
        console.clearAndWrite("Successfully saved on " + currentMenuSave->getLabel() + " (" + date + ").");
        console.setNextState(GameState::INMENU);
        view.show(ViewLayer::MENU);
        // if autosave
    }
    else if (state == GameState::INOVERWORLD)
    {
        console.clearAndWrite("Progress saved on " + currentMenuSave->getLabel() + ".");
        console.setNextState(GameState::INOVERWORLD);
        view.show(ViewLayer::OVERWORLD);
    }

    state = GameState::INCONSOLE;
    view.show(ViewLayer::CONSOLE);
}

void Game::exit()
{
    view.getWindow().close();
}

GameState Game::getState()
{
    return state;
}

void Game::setState(GameState state)
{
    this->state = state;
}

Overworld* Game::getOverworld()
{
    return overworld;
}

Console* Game::getConsole()
{
    return &console;
}

void Game::toggleMute(sf::Music& music)
{
    mute = !mute;

    if (mute)
    {
        music.pause();
    }
    else
    {
        music.play();
    }
}

bool Game::isMute()
{
    return mute;
}
