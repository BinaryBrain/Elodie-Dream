#include "Game.h"

// Initialisation of the singleton to NULL
Game* Game::gameInstance = NULL;

Game::Game() {
    FileHandler::createDirIfNotExisting("save");

    mute = DEFAULT_MUTE;

    title = new TitleScreen(&view);
    overworld = new Overworld(&view, DEFAULT_MUTE);
    scoreBoard = new ScoreBoard(&view);
    statsBoard = new StatsBoard(&view);
    console = new Console(&view);
    menuHandler = new MenuHandler(&view);
    girly = new Girly(&view);
    hud = new Hud(&view);

    saveHandler = SaveHandler::getInstance();
    soundManager = SoundManager::getInstance();
    scoreManager = ScoreManager::getInstance();

    event = new EventHandler(view.getWindow());

    menuHandler->setInLevel(false);
    view.show(ViewLayer::TITLESCREEN);
}

Game::~Game() {
    if (title) {
        delete title;
    }
    if (event) {
        delete event;
    }
    if (menuHandler) {
        delete menuHandler;
    }
    if (overworld) {
        delete overworld;
    }
    if (console) {
        delete console;
    }
    if (girly) {
        delete girly;
    }
    if (hud) {
        delete hud;
    }
}

// Gets the instance of the game
Game* Game::getInstance() {
    if (!gameInstance) {
        gameInstance = new Game();
    }
    return gameInstance;
}

void Game::kill() {
    if (gameInstance) {
        delete gameInstance;
        gameInstance = NULL;
    }
}

void Game::leaveLevel() {
    state = GameState::INOVERWORLD;
    view.hide(ViewLayer::SKY);
    view.hide(ViewLayer::EARTH);
    view.hide(ViewLayer::LEVEL);
    view.hide(ViewLayer::HUD);
    view.hide(ViewLayer::CONSOLE);
    view.show(ViewLayer::OVERWORLD);
    if (!isMute() && overworld->getMusic()->getStatus() != sf::Music::Status::Playing) {
        overworld->getMusic()->play();
    }
    overworld->getElodie()->stand();
    overworld->resetPos();

    if (curLevel) {
        delete curLevel;
        curLevel = NULL;
    }
    scoreManager->resetCurrentScore();
    menuHandler->getTitleMenu()->toNormalMenu();
}

void Game::displayLevel(int curLevelNbr, sf::Time time) {
    //double ypos = ((Elodie*)curLevel->getEntities()["elodie"])->getPosition().y;
    //if (  ypos < miny) {
    //    miny = ypos;
    //}
    if (showTutoConsole) {
        state = GameState::INCONSOLE;
        curLevel->pause();
        view.show(ViewLayer::CONSOLE);
        const char *tutorial = "You learned the existence of a legendary poro land, where you can find all the poros. More than interested, you begin your long journey to find this mysterious country...\n"
                               "As you progress, you will surely come across some animals or monsters, like this sheep there.\n"
                               "You can press 'A' to kill them or just jump over them with the space bar.\n"
                               "Well, good luck, you might need it! :3\n"
                               "   Alia";
        console->clearAndWrite(tutorial);
        console->setNextState(GameState::INLEVEL);
        showTutoConsole = false;

    } else if (showCastleConsole) {
        state = GameState::INCONSOLE;
        curLevel->pause();
        view.show(ViewLayer::CONSOLE);
        const char *castle = "It is such a dark and scary place for a pretty girl like you, isn't it ? Press G to make it better <3\n"
                               "Good luck again, pretty ! :3\n"
                               "   Alia";
        console->clearAndWrite(castle);
        console->setNextState(GameState::INLEVEL);
        showCastleConsole = false;
    }
    // leave level
    if (event->keyIsPressed(sf::Keyboard::Escape)) {
        defaultReturnState = state;
        state = GameState::INMENU;
        curLevel->pause();
        menuHandler->setNextState(GameState::INLEVEL);
        menuHandler->resetMenu();
        view.show(ViewLayer::MENU);
        menuHandler->setInLevel(true);
        // toggle sound
    } else if(event->keyIsPressed(sf::Keyboard::M)) {
        toggleMute();
        // the level
    } else {
        curLevel->live(event, time);
        hud->setLevel(((Elodie*)curLevel->getEntities()["elodie"])->getImmersionLevel());
        hud->setScore(scoreManager->getCurrentScore().getLevelPoints());

        // level finished
        if (curLevel->isFinished()) {
            scoreManager->setLevel(curLevelNbr);
            scoreManager->computeTotalPoints();

            // end of game
            if (curLevelNbr == (NUMLEVELS-1)) {
                endingScreen = new EndingScreen(&view, mute);
                view.hide(ViewLayer::LEVEL);
                view.hide(ViewLayer::SKY);
                view.hide(ViewLayer::EARTH);
                view.show(ViewLayer::ENDINGSCREEN);
                if(curLevel) {
                    delete curLevel;
                    curLevel = NULL;
                }
                state = GameState::ENDINGSCREEN;
            } else {
                scoreBoard->prepareText();

                view.hide(ViewLayer::LEVEL);
                view.hide(ViewLayer::SKY);
                view.hide(ViewLayer::EARTH);
                view.show(ViewLayer::SCORE);
                if(curLevel) {
                    delete curLevel;
                    curLevel = NULL;
                }
                state = GameState::INSCORE;
            }

            scoreManager->saveCurrentScore();
            scoreManager->resetCurrentScore();
            menuHandler->getTitleMenu()->toNormalMenu();

        // wake up
        } else if (curLevel->mustDie() && !GOD_MODE) {
            death = new Death(&view, mute);
            view.hide(ViewLayer::LEVEL);
            view.hide(ViewLayer::SKY);
            view.hide(ViewLayer::EARTH);
            view.show(ViewLayer::DEATH);
            if (curLevel) {
                delete curLevel;
                curLevel = NULL;
            }
            state = GameState::DEAD;
        }
    }
}

void Game::loadLevel(int levelNbr) {
    state = GameState::INLEVEL;
    curLevelNbr = levelNbr;
    LevelEnv env = LevelEnv::FIELD;
    switch (levelNbr) {
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
    curLevel = new Level(&view, "assets/levels/level"+Utils::itos(curLevelNbr)+".txt", env, overworld->getElodie());
    menuHandler->getTitleMenu()->toLevelMenu();
}

void Game::handleOverworld(sf::Time time) {
    Elodie* elo = overworld->getElodie();

    if (elo->isMoving()) {
        elo->overworldMove(time.asSeconds());
    } else if (event->keyIsHold(sf::Keyboard::Down)) {
        elo->setDistanceToMove(overworld->moveDown());
        if (elo->hasToMove()) {
            elo->setWalkDown();
        }
    } else if (event->keyIsHold(sf::Keyboard::Up)) {
        elo->setDistanceToMove(overworld->moveUp());
        if (elo->hasToMove()) {
            elo->setWalkUp();
        }
    } else if (event->keyIsHold(sf::Keyboard::Left)) {
        elo->setDistanceToMove(overworld->moveLeft());
        if (elo->hasToMove()) {
            elo->setWalkLeft();
        }
    } else if (event->keyIsHold(sf::Keyboard::Right)) {
        elo->setDistanceToMove(overworld->moveRight());
        if (elo->hasToMove()) {
            elo->setWalkRight();
        }
    } else if (event->keyIsPressed(sf::Keyboard::Return) || event->keyIsPressed(sf::Keyboard::Space)) {
        if (overworld->getLevelToLoad() >= 0) {
            loadLevel(overworld->getLevelToLoad());
            view.hide(ViewLayer::OVERWORLD);
            overworld->getMusic()->stop();
            view.show(ViewLayer::SKY);
            view.show(ViewLayer::EARTH);
            view.show(ViewLayer::LEVEL);
            view.show(ViewLayer::HUD);
        }
    } else if (event->keyIsPressed(sf::Keyboard::Escape)) {
        menuHandler->resetMenu();
        defaultReturnState = state;
        state = GameState::INMENU;
        menuHandler->setNextState(GameState::INOVERWORLD);
        view.show(ViewLayer::MENU);
        menuHandler->setInLevel(false);
        // testing purposes
    } else if (event->keyIsPressed(sf::Keyboard::M)) {
        toggleMute();
        // testing purposes
    }
    elo->update(time);
}

void Game::displayMenu() {
    if (event->keyIsPressed(sf::Keyboard::Down)) {
        menuHandler->incIndex();
    }
    if (event->keyIsPressed(sf::Keyboard::Up)) {
        menuHandler->decIndex();
    }
    if (event->keyIsPressed(sf::Keyboard::Return)) {
        currentMenuComponent = menuHandler->getCurrentMenuComponent();
        state = currentMenuComponent->getState();

        if (state == GameState::INOVERWORLD) {
            leaveLevel();
            view.hide(ViewLayer::MENU);
            overworld->getElodie()->play();
            view.hide(ViewLayer::TITLESCREEN);

        } else if (state == GameState::INLEVEL) {
            if (curLevel) {
                state = GameState::INLEVEL;
                view.hide(ViewLayer::MENU);
                view.show(ViewLayer::LEVEL);
                view.show(ViewLayer::HUD);
                curLevel->play(&frameClock);
            } else {
                std::cerr << "Must display level but not initialized." << std::endl;
            }

        } else if (state == GameState::SAVE) {
            // sets the current slot and name
            autoSave = true;
            currentMenuSave = currentMenuComponent;
        } else if (state == GameState::INSTATS) {
            statsBoard->prepareText();
            view.hide(ViewLayer::MENU);
            view.show(ViewLayer::STATS);
        }

    } else if (event->keyIsPressed(sf::Keyboard::Escape)) {
        defaultReturnState = state;
        state = menuHandler->getNextState();
        if (state == GameState::INOVERWORLD) {
            view.hide(ViewLayer::MENU);
            view.show(ViewLayer::OVERWORLD);
            overworld->getElodie()->stand();
            overworld->resetPos();
            if (curLevel) {
                delete curLevel;
                curLevel = NULL;
            }
        } else if (state == GameState::INLEVEL) {
            if (curLevel) {
                state = GameState::INLEVEL;
                view.hide(ViewLayer::MENU);
                view.show(ViewLayer::LEVEL);
                view.show(ViewLayer::HUD);
                curLevel->play(&frameClock);
            } else {
                std::cerr << "Must display level but not initialized." << std::endl;
            }
        }
    } else if (event->keyIsPressed(sf::Keyboard::M)) {
        toggleMute();
    }
}

void Game::displayConsole() {
    if (event->keyIsPressed(sf::Keyboard::Up)) {
        console->previousPage();
    }
    if (event->keyIsPressed(sf::Keyboard::Down)) {
        console->nextPage();
    }
    if (event->keyIsPressed(sf::Keyboard::Space) || event->keyIsPressed(sf::Keyboard::Return)) {
        state = console->getNextState();
        if (state == GameState::INOVERWORLD) {
            view.hide(ViewLayer::CONSOLE);
            view.hide(ViewLayer::MENU);
            view.show(ViewLayer::OVERWORLD);
            view.hide(ViewLayer::TITLESCREEN);
        } else if (state == GameState::INLEVEL) {
            if (curLevel) {
                state = GameState::INLEVEL;
                view.hide(ViewLayer::CONSOLE);
                view.show(ViewLayer::LEVEL);
                curLevel->play(&frameClock);
            } else {
                std::cerr << "Must display level but not initialized." << std::endl;
            }
        } else if (state == GameState::INMENU) {
            view.hide(ViewLayer::CONSOLE);
            view.show(ViewLayer::MENU);
        }
    }
}

void Game::dead() {
    if (event->keyIsPressed(sf::Keyboard::Return) || event->keyIsPressed(sf::Keyboard::Space) ) {
        leaveLevel();
        view.hide(ViewLayer::DEATH);
        if (death) {
            delete death;
            death = NULL;
        }
    } else if (event->keyIsPressed(sf::Keyboard::M)) {
        toggleMute();
    }
}

void Game::displayEnd() {
    if (event->keyIsPressed(sf::Keyboard::Return) || event->keyIsPressed(sf::Keyboard::Space)) {
        leaveLevel();
        view.hide(ViewLayer::ENDINGSCREEN);
        if (endingScreen) {
            delete endingScreen;
            endingScreen = NULL;
        }
    }
}

void Game::displayScore() {
    if (event->keyIsPressed(sf::Keyboard::Return) || event->keyIsPressed(sf::Keyboard::Space)) {
        leaveLevel();
        view.hide(ViewLayer::SCORE);
        view.show(ViewLayer::OVERWORLD);
        overworld->evolve(overworld->getState(), curLevelNbr + 1);
        overworld->setToLevel(curLevelNbr + 1);
        overworld->resetPos();
        menuHandler->getTitleMenu()->toNormalMenu();
        statsBoard->setLDL(overworld->getState());

        if (autoSave) {
            save();
        }
    }
}

void Game::displayStats() {
    if (event->keyIsPressed(sf::Keyboard::Return) || event->keyIsPressed(sf::Keyboard::Escape)) {
        view.hide(ViewLayer::STATS);
        view.show(ViewLayer::MENU);
        state = GameState::INMENU;
    }
}

void Game::run() {
    sf::RenderWindow* window = view.getWindow();
    view.show(ViewLayer::MENU);

    window->setFramerateLimit(FPS);
    window->setIcon(icon.width, icon.height, icon.pixel_data);

    while (window->isOpen()) {
        sf::Time sfTime = sf::seconds(1.0/FPS);//frameClock.restart();
        //if (sfTime.asSeconds() > MAX_TIME_FRAME)
        //    sfTime = sf::seconds(MAX_TIME_FRAME);
        //std::cout << 1.0/sfTime.asSeconds() << std::endl;
        //totframe++;
        //frametime += sfTime.asSeconds();
        event->listening();

        if (event->lostFocus()) {
            if (curLevel) {
                pausePrevState = state;
                state = GameState::PAUSE;
                curLevel->pause();
            }
        }

        if (event->gainedFocus()) {
            if (curLevel) {
                state = pausePrevState;
                curLevel->play(&frameClock);
            }
        }

        if (event->keyIsPressed(sf::Keyboard::F12)) {
            sf::Image screen = window->capture();
            now.refreshTime();

            std::string date = now.getDMY("-") + "_" + now.getHMS("-");
            std::string screensDirPath = "screenshots";

            FileHandler::createDirIfNotExisting(screensDirPath);
            screen.saveToFile(screensDirPath+"/"+date+".jpg");
        }

        if (event->keyIsPressed(sf::Keyboard::G)) {
            girlyMode = !girlyMode;
        }

        switch(state) {
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
        if (girlyMode) {
            view.show(ViewLayer::GIRLY);
        }

        view.draw();
    }

    //double result = frametime/totframe;

    //std::cout << "Res :" << miny << std::endl;
    //char hihi;
    //std::cin >> hihi;
}

void Game::newGame() {
    if (curLevel) {
        leaveLevel();
    }
    if (overworld) {
        delete overworld;
        overworld = NULL;
    }
    overworld = new Overworld(&view, mute);
    view.addView(ViewLayer::OVERWORLD, overworld);
    state = GameState::INOVERWORLD;
    view.hide(ViewLayer::MENU);
    view.show(ViewLayer::OVERWORLD);
    view.hide(ViewLayer::TITLESCREEN);
    scoreManager->resetAllScores();
    statsBoard->setLDL(0);
    menuHandler->getTitleMenu()->toNormalMenu();

    // if there is a free slot, save on it
    std::string nextFreeSlot = saveHandler->nextFreeSlot();

    if (nextFreeSlot != "") {
        currentMenuSave = menuHandler->getMenuComponentFromKey(nextFreeSlot);
        save();
        autoSave = true;
    } else {
        autoSave = false;
    }
}

void Game::load() {
    std::string path = "save/" + currentMenuComponent->getLabel() + ".save";
    std::string tempJsonFilePath = "save/temp.json";

    if (FileHandler::fileExists(path)) {
        // resets the scores
        scoreManager->resetAllScores();

        // Sets the slot and text (for example for the autosave)
        autoSave = true;
        currentMenuSave = currentMenuComponent;

        saveHandler->setPath(path);
        FileHandler::writeContent(tempJsonFilePath, saveHandler->load());

        // retrieves the saved values
        JsonAccessor accessor;
        bool jsonReady = accessor.load(tempJsonFilePath);

        // if the save is valid
        if (accessor.canTakeElementFrom("date") && accessor.canTakeElementFrom("lastdiscoveredlevel") && jsonReady) {
            std::string date = accessor.getString("date");
            int LDL = accessor.getInt("lastdiscoveredlevel");

            // if the version number exists
            if (accessor.canTakeElementFrom("version")) {
                std::vector< std::vector<int>* > datas = *(accessor.getInt2DVector("scoresdatas"));
                std::vector< std::vector<int> > scoreDatas;

                for (size_t i = 0; i < datas.size(); ++i) {
                    std::vector<int> score = *(datas[i]);
                    scoreDatas.push_back(score);
                }

                scoreManager->setAllDatas(scoreDatas);
                std::cout << "Save from version " << accessor.getDouble("version") << std::endl;

            } else {
                std::cout << "Save from version prior to 1.1" << std::endl;
                scoreManager->resetAllScores();
            }


            if (curLevel) {
                leaveLevel();
            }
            if (!overworld) {
                overworld = new Overworld(&view, mute);
                view.addView(ViewLayer::OVERWORLD, overworld);
            }
            overworld->setState(LDL);
            overworld->setToLevel(LDL);
            overworld->resetPos();
            overworld->getElodie()->play();

            statsBoard->setLDL(LDL);

            console->clearAndWrite("Successfully loaded " + currentMenuComponent->getLabel() + ", from " + date + ".");
            console->setNextState(GameState::INOVERWORLD);

            menuHandler->getTitleMenu()->toNormalMenu();

        } else {
            console->clearAndWrite("Save corrupted.");
            console->setNextState(GameState::INMENU);
        }

        accessor.close();

        // remove the temporary json
        FileHandler::deleteFile(tempJsonFilePath);

    } else {
        console->clearAndWrite("Save doesn't exist.");
        console->setNextState(GameState::INMENU);
    }

    state = GameState::INCONSOLE;
    view.show(ViewLayer::MENU);
    view.show(ViewLayer::CONSOLE);
}

void Game::save() {

    // creates date
    now.refreshTime();
    std::string date = "the " + now.getDMY("/") + ", at " + now.getHMS(":");

    // creates save with current slot and name
    std::string path = "save/" + currentMenuSave->getLabel() + ".save";

    int LDL = overworld->getState();

    // Displays the save name on the menu
    currentMenuSave->getText()->setString(saveHandler->computeLDLName(LDL));

    std::vector< std::vector<int> > scoresDatas = scoreManager->getAllDatas();

    // saves the datas to the save file
    std::string keyVersion = "version";
    std::string keyDate = "date";
    std::string keyLDL = "lastdiscoveredlevel";
    std::string keyScoresDatas = "scoresdatas";

    JsonStringifier* stringifier = saveHandler->getStringifier();
    stringifier->add(keyVersion, GAME_VERSION);
    stringifier->add(keyDate, date);
    stringifier->add(keyLDL, LDL);
    stringifier->add(keyScoresDatas, scoresDatas);

    saveHandler->setPath(path);
    saveHandler->save();
    saveHandler->clearStringifier();

    // console confirmation
    // save() called from the menu
    if (state == GameState::SAVE) {
        console->clearAndWrite("Successfully saved on " + currentMenuSave->getLabel() + " (" + date + ").");
        console->setNextState(GameState::INMENU);

        state = GameState::INCONSOLE;
        view.show(ViewLayer::MENU);
        view.show(ViewLayer::CONSOLE);
    // if autosave
    } else if (state == GameState::INOVERWORLD) {
        console->clearAndWrite("Progress saved on " + currentMenuSave->getLabel() + ".");
        console->setNextState(GameState::INOVERWORLD);

        state = GameState::INCONSOLE;
        view.show(ViewLayer::OVERWORLD);
        view.show(ViewLayer::CONSOLE);
    }

}

void Game::exit() {
    view.getWindow()->close();
}

GameState Game::getState() {
    return state;
}

void Game::setState(GameState state) {
    this->state = state;
}

Overworld* Game::getOverworld() {
    return overworld;
}

Console* Game::getConsole() {
    return console;
}

void Game::toggleMute() {
    mute = !mute;

    if (state == GameState::INLEVEL && curLevel) {
        if (mute) {
            curLevel->getMusic()->pause();
        } else {
            curLevel->getMusic()->play();
        }
    } else if (state == GameState::DEAD) {
        if (mute) {
            death->getMusic()->pause();
        } else {
            death->getMusic()->play();
        }
    } else {
        if (mute) {
            overworld->getMusic()->pause();
        } else {
            overworld->getMusic()->play();
        }
    }
}

bool Game::isMute() {
    return mute;
}
