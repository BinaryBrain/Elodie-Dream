#include "Game.h"

// Initialisation of the singleton to NULL
Game* Game::gameInstance = NULL;

Game::Game() {
    mute = DEFAULT_MUTE;

    console = new Console(&view);
    event = new EventHandler(view.getWindow());
    overworld = new Overworld(&view);
    menuHandler = new MenuHandler(&view);
    girly = new Girly(&view);
    immBar = new ImmersionBar(&view);
    death = new Death(&view);
    soundManager = SoundManager::getInstance();

    view.addView(ViewLayer::MENU, menuHandler);
    view.addView(ViewLayer::OVERWORLD, overworld);
    view.addView(ViewLayer::CONSOLE, console);
    view.addView(ViewLayer::DEATH, death);

    // testing purposes
    view.addView(ViewLayer::GIRLY, girly);

    view.addView(ViewLayer::IMMERSIONBAR, immBar);

    // testing purposes
    JsonAccessor language = JsonAccessor();
    language.load("assets/config/languages/FR.lang");
    console->addParagraph(language.getString("ConsoleTest"));
    console->addParagraph(language.getString("ConsoleTest2"));
    console->setCurrentPage(0);
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

void Game::displayLevel(int curLevelNbr, sf::Time time) {
    if(event->keyIsPressed(sf::Keyboard::Return)) {
        state = GameState::INOVERWORLD;

        view.reset(ViewLayer::LEVEL);
        view.hide(ViewLayer::LEVEL);
        view.hide(ViewLayer::IMMERSIONBAR);
        view.hide(ViewLayer::CONSOLE);
        view.show(ViewLayer::OVERWORLD);
        overworld->getMusic()->play();

        overworld->getElodie()->stand();
        overworld->resetPos();

        if(curLevel) {
            delete curLevel;
            curLevel = NULL;
        }
    } else if (event->keyIsPressed(sf::Keyboard::P)) {
        state = GameState::INMENU;
        curLevel->pause();
        menuHandler->setNextState(GameState::INLEVEL);
        view.show(ViewLayer::MENU);
    } else if(event->keyIsPressed(sf::Keyboard::M)) {
        toggleMute();
    }
    // testing purposes
    else if (event->keyIsPressed(sf::Keyboard::A)) {
        soundManager->play(SoundType::PUNCH);
    } else if (event->keyIsPressed(sf::Keyboard::C)) {
        state = GameState::INCONSOLE;
        curLevel->pause();
        console->setNextState(GameState::INLEVEL);
        view.show(ViewLayer::CONSOLE);
    } else {
        curLevel->live(event, time);
        immBar->setLevel(((Elodie*)curLevel->getEntities()["elodie"])->getImmersionLevel());
        if (((Elodie*)curLevel->getEntities()["elodie"])->getImmersionLevel() <= 0 && !GOD_MODE) {
            view.hide(ViewLayer::LEVEL);
            view.show(ViewLayer::DEATH);
            console->clear();
            console->addParagraph("You woke up...");
            console->setCurrentPage(0);
            view.show(ViewLayer::CONSOLE);
            view.hide(ViewLayer::IMMERSIONBAR);
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
    curLevel = new Level(&view, "assets/levels/level_sheep.txt", LevelEnv::FIELD, overworld->getElodie());
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
        loadLevel(0);
        view.hide(ViewLayer::OVERWORLD);
        overworld->getMusic()->stop();
        view.show(ViewLayer::LEVEL);
        view.show(ViewLayer::IMMERSIONBAR);
    } else if (event->keyIsPressed(sf::Keyboard::P)) {
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
        std::pair<GameState, std::string> p = menuHandler->execute();
        state = p.first;
        currentMenuItem = p.second;
        if (state == GameState::INOVERWORLD) {
            view.hide(ViewLayer::IMMERSIONBAR);
            view.hide(ViewLayer::LEVEL);
            view.hide(ViewLayer::MENU);
            view.show(ViewLayer::OVERWORLD);
            overworld->getElodie()->stand();
            overworld->resetPos();
            overworld->getElodie()->play();
        }
    } else if(event->keyIsPressed(sf::Keyboard::P)) {
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
            view.show(ViewLayer::OVERWORLD);
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
        view.hide(ViewLayer::CONSOLE);
        view.hide(ViewLayer::DEATH);
        view.show(ViewLayer::OVERWORLD);

        if(!isMute()) {
            overworld->getMusic()->play();
        }

        overworld->getElodie()->stand();
        overworld->resetPos();
        state = GameState::INOVERWORLD;
    }
}

void Game::run() {
    sf::RenderWindow* window = view.getWindow();
    view.show(ViewLayer::MENU);

    window->setFramerateLimit(FPS);

    while (window->isOpen()) {
        sf::Time sfTime = frameClock.restart();
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
        default :
            std::cout << "Error: unknown state" << std::endl;
            break;
        }


        view.hide(ViewLayer::GIRLY);

        if (girlyMode) {
            view.show(ViewLayer::GIRLY);
        }

        view.draw();
    }

}

void Game::load() {
    std::string path = "save/" + currentMenuItem + ".save";
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
    if(accessor.canTakeElementFrom("gamestate")) {

        int gameState = accessor.getInt("gamestate");

        console->clear();
        console->addParagraph("Successfully loaded " + currentMenuItem + ".");
        console->setCurrentPage(0);
        console->setNextState(GameState::INMENU);

    } else {
        console->clear();
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

    JsonStringifier dateStringifier;
    JsonAccessor dateAccessor;



    std::string keyDate("date");
    dateStringifier.add(keyDate, date);

    std::ofstream datesFile;
    datesFile.open("save/dates.json");
    datesFile << dateStringifier.getStringifiedDoc() << std::endl;
    datesFile.close();

    // creates save
    std::string path = "save/" + currentMenuItem + ".save";
    SaveHandler* sh = SaveHandler::getInstance();
    sh->setPath(path);
    JsonStringifier* stringifier = sh->getStringifier();

    std::string keyGameState = "gamestate";
    stringifier->add(keyGameState, (int)state);
    sh->save();
    sh->clearStringifier();

    // displays on console
    console->clear();
    console->addParagraph("Successfully saved on " + currentMenuItem + " (" + date + ").");
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

    if(mute) {
        std::cout << "muted" << std::endl;
    } else {
        std::cout << "unmuted" << std::endl;
    }

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
