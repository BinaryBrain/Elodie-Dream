#include "Game.h"

// Initialisation of the singleton to NULL
Game* Game::gameInstance = NULL;

Game::Game() {
    std::string savePath("save");
    if (CreateDirectory(savePath.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError()) {
        // do nothing because it's k
    } else {
        std::cerr << "Could not create save folder." << std::endl;
    }

    mute = DEFAULT_MUTE;

    overworld = new Overworld(&view, DEFAULT_MUTE);
    view.addView(ViewLayer::OVERWORLD, overworld);

    //scoreboard = new Scoreboard(&view);
    //view.addView(ViewLayer::SCORE, scoreboard);

    console = new Console(&view);
    event = new EventHandler(view.getWindow());
    menuHandler = new MenuHandler(&view);
    girly = new Girly(&view);
    immBar = new ImmersionBar(&view);
    soundManager = SoundManager::getInstance();

    view.addView(ViewLayer::MENU, menuHandler);
    view.addView(ViewLayer::CONSOLE, console);
    view.addView(ViewLayer::GIRLY, girly);
    view.addView(ViewLayer::IMMERSIONBAR, immBar);
}

Game::~Game() {
    if (event) {
        delete event;
        event = NULL;
    }
    if (menuHandler) {
        delete menuHandler;
        menuHandler = NULL;
    }

    if (overworld) {
        delete overworld;
        overworld = NULL;
    }

    if(console) {
        delete console;
        console = NULL;
    }

    if (girly) {
        delete girly;
        girly = NULL;
    }

    if (immBar) {
        delete immBar;
        girly = NULL;
    }
}

// Gets the instance of the game
Game* Game::getInstance() {
    if(!gameInstance) gameInstance = new Game();
    return gameInstance;
}

void Game::kill() {
    if(gameInstance) {
        delete gameInstance;
        gameInstance = NULL;
    }
}

void Game::leaveLevel() {
    state = GameState::INOVERWORLD;
    view.hide(ViewLayer::SKY);
    view.hide(ViewLayer::EARTH);
    view.hide(ViewLayer::LEVEL);
    view.hide(ViewLayer::IMMERSIONBAR);
    view.hide(ViewLayer::CONSOLE);
    view.show(ViewLayer::OVERWORLD);
    if(!isMute() && overworld->getMusic()->getStatus() != sf::Music::Status::Playing) {
        overworld->getMusic()->play();
    }
    overworld->getElodie()->stand();
    overworld->resetPos();

    if(curLevel) {
        delete curLevel;
        curLevel = NULL;
    }

}

void Game::displayLevel(int curLevelNbr, sf::Time time) {
    // tutorial
    if (showTutoConsole) {
        state = GameState::INCONSOLE;
        curLevel->pause();
        view.show(ViewLayer::CONSOLE);

        console->clear();
        const char *tutorial = "You learned the existence of a legendary poro land, where you can find all the poros. More than interested, you begin your long journey to find this mysterious country...\n"
                               "As you progress, you will surely come across some animals or monsters, like this sheep there.\n"
                               "You can press 'A' to kill them or just jump over them with the space bar.\n"
                               "Well, good luck, you might need it! :3\n"
                               "   Alia";
        console->addParagraph(tutorial);
        console->setCurrentPage(0);
        console->setNextState(GameState::INLEVEL);
        showTutoConsole = false;
    }
    // leave level
    if(event->keyIsPressed(sf::Keyboard::Return)) {
        leaveLevel();
        // Pause
    } else if (event->keyIsPressed(sf::Keyboard::P)) {
        defaultReturnState = state;
        state = GameState::INMENU;
        curLevel->pause();
        menuHandler->setNextState(GameState::INLEVEL);
        view.show(ViewLayer::MENU);

        // toggle sound
    } else if(event->keyIsPressed(sf::Keyboard::M)) {
        toggleMute();

        // the level
    } else {
        curLevel->live(event, time);
        immBar->setLevel(((Elodie*)curLevel->getEntities()["elodie"])->getImmersionLevel());

        if(curLevel->isFinished()) {
            view.hide(ViewLayer::LEVEL);
            view.hide(ViewLayer::SKY);
            view.hide(ViewLayer::EARTH);
            view.show(ViewLayer::OVERWORLD);
            overworld->evolve(overworld->getState(), curLevelNbr + 1);
            leaveLevel();
            if(curLevel) {
                delete curLevel;
                curLevel = NULL;
            }
            state = GameState::INOVERWORLD;
        } else if (curLevel->mustDie() && !GOD_MODE) {
            death = new Death(&view, mute);

            view.hide(ViewLayer::LEVEL);
            view.hide(ViewLayer::SKY);
            view.hide(ViewLayer::EARTH);
            view.show(ViewLayer::DEATH);
            if(curLevel) {
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
    switch(levelNbr) {
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
}

void Game::handleOverworld(sf::Time time) {
    if (event->keyIsPressed(sf::Keyboard::N)) {
        overworld->evolve();
    }

    if(overworld->getElodie()->isMoving()) {
        overworld->getElodie()->overworldMove(time.asSeconds());
    } else if (event->keyIsHold(sf::Keyboard::Down)) {
        overworld->getElodie()->setDistanceToMove(overworld->moveDown());
        if(overworld->getElodie()->hasToMove()) {
            overworld->getElodie()->setWalkDown();
        }
    } else if (event->keyIsHold(sf::Keyboard::Up)) {
        overworld->getElodie()->setDistanceToMove(overworld->moveUp());
        if(overworld->getElodie()->hasToMove()) {
            overworld->getElodie()->setWalkUp();
        }
    } else if (event->keyIsHold(sf::Keyboard::Left)) {
        overworld->getElodie()->setDistanceToMove(overworld->moveLeft());
        if(overworld->getElodie()->hasToMove()) {
            overworld->getElodie()->setWalkLeft();
        }
    } else if (event->keyIsHold(sf::Keyboard::Right)) {
        overworld->getElodie()->setDistanceToMove(overworld->moveRight());
        if(overworld->getElodie()->hasToMove()) {
            overworld->getElodie()->setWalkRight();
        }
    } else if (event->keyIsPressed(sf::Keyboard::Return)) {
        if(overworld->getLevelToLoad() >= 0) {
            loadLevel(overworld->getLevelToLoad());
            view.hide(ViewLayer::OVERWORLD);
            overworld->getMusic()->stop();
            view.show(ViewLayer::SKY);
            view.show(ViewLayer::EARTH);
            view.show(ViewLayer::LEVEL);
            view.show(ViewLayer::IMMERSIONBAR);
        }
    } else if (event->keyIsPressed(sf::Keyboard::P)) {
        defaultReturnState = state;
        state = GameState::INMENU;
        menuHandler->setNextState(GameState::INOVERWORLD);
        view.show(ViewLayer::MENU);
        // testing purposes
    } else if (event->keyIsPressed(sf::Keyboard::M)) {
        toggleMute();
        // testing purposes
    } else if (event->keyIsPressed(sf::Keyboard::C)) {
        state = GameState::INCONSOLE;
        console->setNextState(GameState::INOVERWORLD);
        view.show(ViewLayer::CONSOLE);
    }
    overworld->getElodie()->update(time);
}

void Game::displayMenu() {
    if (event->keyIsPressed(sf::Keyboard::Down)) menuHandler->incIndex();
    if (event->keyIsPressed(sf::Keyboard::Up)) menuHandler->decIndex();
    if (event->keyIsPressed(sf::Keyboard::Return)) {
        std::pair<GameState, MenuComponent*> p = menuHandler->execute();
        state = p.first;
        currentMenuItem = p.second;
        if(state == GameState::INOVERWORLD) {
            Menu* title = menuHandler->getTitleMenu();
            title->hideBackground();
        }
        if (state == GameState::INOVERWORLD) {
            leaveLevel();
            view.hide(ViewLayer::MENU);
            overworld->getElodie()->play();
        }
    } else if(event->keyIsPressed(sf::Keyboard::P)) {
        defaultReturnState = state;
        state = menuHandler->getNextState();
        if (state == GameState::INOVERWORLD) {
            view.hide(ViewLayer::MENU);
            view.show(ViewLayer::OVERWORLD);
            overworld->getElodie()->stand();
            overworld->resetPos();
            if(curLevel) {
                delete curLevel;
                curLevel = NULL;
            }
        } else if (state == GameState::INLEVEL) {
            if(curLevel) {
                state = GameState::INLEVEL;
                view.hide(ViewLayer::MENU);
                view.show(ViewLayer::LEVEL);
                view.show(ViewLayer::IMMERSIONBAR);
                curLevel->play(&frameClock);
            } else {
                std::cerr << "Must display level but not initialized." << std::endl;
            }
        }
    } else if (event->keyIsPressed(sf::Keyboard::M)) {
        toggleMute();
    } else if (event->keyIsPressed(sf::Keyboard::C)) {
        state = GameState::INCONSOLE;
        console->setNextState(GameState::INMENU);
        view.show(ViewLayer::CONSOLE);
    }
}

void Game::displayConsole() {

    if (event->keyIsPressed(sf::Keyboard::Up)) console->previousPage();
    if (event->keyIsPressed(sf::Keyboard::Down)) console->nextPage();
    if(event->keyIsPressed(sf::Keyboard::C)) {
        state = console->getNextState();
        if (state == GameState::INOVERWORLD) {
            view.hide(ViewLayer::CONSOLE);
            view.hide(ViewLayer::MENU);
            view.show(ViewLayer::OVERWORLD);
            menuHandler->getTitleMenu()->hideBackground();
        } else if (state == GameState::INLEVEL) {
            if(curLevel) {
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
    if (event->keyIsPressed(sf::Keyboard::Return)) {
        leaveLevel();
        view.hide(ViewLayer::DEATH);
        if(death) {
            delete death;
            death = NULL;
        }
    }
}

void Game::run() {
    sf::RenderWindow* window = view.getWindow();
    view.show(ViewLayer::MENU);

    window->setFramerateLimit(FPS);

    while (window->isOpen()) {
        sf::Time sfTime = frameClock.restart();
        if (sfTime.asSeconds() > MAX_TIME_FRAME)
            sfTime = sf::seconds(MAX_TIME_FRAME);
        //std::cout << 1.0/sfTime.asSeconds() << std::endl;
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

        if (event->keyIsHold(sf::Keyboard::Escape)) {
            window->close();
        }

        if (event->keyIsPressed(sf::Keyboard::F12)) {
            sf::Image screen = window->capture();

            // creates date
            time_t t = time(0);
            struct tm* now = localtime(&t);
            std::string date("");
            date += Utils::itos(now->tm_mday) + "-" + Utils::itos(now->tm_mon + 1) + "-" + Utils::itos(now->tm_year + 1900) + " ";
            date += Utils::itos(now->tm_hour) + "-" + Utils::itos(now->tm_min) + "-" + Utils::itos(now->tm_sec);

            screen.saveToFile("screenshots/"+date+".jpg");
        }

        if (event->mouseIsPressed(sf::Mouse::Left)) {
            eventMouse leftClick(event->mouseInfoPressed(sf::Mouse::Left));
            std::cout << "Mouse pos : (" << leftClick.x << "; " << leftClick.y << ")" << std::endl;
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
        default :
            std::cerr << "Error: unknown state" << std::endl;
            break;
        }


        view.hide(ViewLayer::GIRLY);
        //view.hide(ViewLayer::SCORE);
        //view.show(ViewLayer::SCORE);
        if (girlyMode) {
            view.show(ViewLayer::GIRLY);
        }

        view.draw();
    }

}

void Game::newGame() {
    if(curLevel) {
        leaveLevel();
    }
    if(overworld) {
        delete overworld;
        overworld = NULL;
    }
    overworld = new Overworld(&view, mute);
    view.addView(ViewLayer::OVERWORLD, overworld);
    state = GameState::INOVERWORLD;
    view.hide(ViewLayer::MENU);
    view.show(ViewLayer::OVERWORLD);
    menuHandler->getTitleMenu()->hideBackground();
}

void Game::load() {
    std::string path = "save/" + currentMenuItem->getLabel() + ".save";
    SaveHandler* sh = SaveHandler::getInstance();
    sh->setPath(path);

    std::string json = sh->load();

    // creates a temporary json file for the JsonAccessor
    std::ofstream tempJsonFile;
    std::string tempJsonFilePath = "save/temp.json";

    tempJsonFile.open(tempJsonFilePath);
    tempJsonFile << json << std::endl;
    tempJsonFile.close();

    JsonAccessor accessor;
    accessor.load(tempJsonFilePath);
    if(accessor.canTakeElementFrom("date")) {
        std::string date = accessor.getString("date");
        int LDL = accessor.getInt("lastdiscoveredlevel");
        if(curLevel) {
            leaveLevel();
        }
        if(!overworld) {
            overworld = new Overworld(&view, mute);
            view.addView(ViewLayer::OVERWORLD, overworld);
        }
        overworld->setState(LDL);
        overworld->setPosInPath(0);
        overworld->resetPos();

        console->clear();
        console->setNextState(GameState::INOVERWORLD);
        console->addParagraph("Successfully loaded " + currentMenuItem->getLabel() + ", from " + date);
        console->setCurrentPage(0);

    } else {
        console->clear();
        console->setNextState(defaultReturnState);
        console->addParagraph("Save doesn't exist.");
        console->setCurrentPage(0);
        console->setNextState(GameState::INMENU);
    }

    accessor.close();

    // remove the temporary json
    if(remove(tempJsonFilePath.c_str()) != 0 ) {
        std::cerr << "Error deleting temporary json" << std::endl;
    }

    state = GameState::INCONSOLE;
    view.show(ViewLayer::MENU);
    view.show(ViewLayer::CONSOLE);
}

void Game::save() {

    // creates date
    time_t t = time(0);
    struct tm* now = localtime(&t);
    std::string date("the ");
    date += Utils::itos(now->tm_mday) + "/" + Utils::itos(now->tm_mon + 1) + "/" + Utils::itos(now->tm_year + 1900) + ", at ";
    date += Utils::itos(now->tm_hour) + ":" + Utils::itos(now->tm_min) + ":" + Utils::itos(now->tm_sec);


    // creates save
    std::string path = "save/" + currentMenuItem->getLabel() + ".save";
    SaveHandler* sh = SaveHandler::getInstance();
    sh->setPath(path);
    JsonStringifier* stringifier = sh->getStringifier();

    std::string keyDate("date");
    stringifier->add(keyDate, date);

    int LDL = overworld->getState();
    sf::Text* txt = currentMenuItem->getText();
    if(LDL == 0) {
        txt->setString("Tutorial");
    } else {
        txt->setString("Level " + Utils::itos(LDL));
    }

    std::string keyLDL("lastdiscoveredlevel");
    stringifier->add(keyLDL, LDL);

    sh->save();
    sh->clearStringifier();

    // displays on console
    console->clear();
    console->addParagraph("Successfully saved on " + currentMenuItem->getLabel() + " (" + date + ").");
    console->setCurrentPage(0);
    console->setNextState(GameState::INMENU);

    state = GameState::INCONSOLE;
    view.show(ViewLayer::MENU);
    view.show(ViewLayer::CONSOLE);
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
        if(mute) {
            curLevel->getMusic()->pause();
        } else {
            curLevel->getMusic()->play();
        }
    } else {
        if(mute) {
            overworld->getMusic()->pause();
        } else {
            overworld->getMusic()->play();
        }
    }
}

bool Game::isMute() {
    return mute;
}
