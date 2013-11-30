#include "Game.h"

// Initialisation of the singleton to NULL
Game* Game::gameInstance = NULL;

Game::Game() {
    view.addView(ViewLayer::MENU, menuHandler);
    view.addView(ViewLayer::OVERWORLD, overworld);
    view.addView(ViewLayer::CONSOLE, console);

    // testing purposes
    view.addView(ViewLayer::GIRLY, girly);

    // testing purposes
    JsonAccessor language = JsonAccessor();
    language.load("assets/config/languages/EN.lang");
    console->addSentence(language.getString("ConsoleTest"));
    console->setCurrentPage(0, view.getWindow()->getSize().x, view.getWindow()->getSize().y);

    /*
    console->addSentence("Fnu\nla\nvie\non\nmultiple\nlines\n:3.");
    */
}

Game::~Game() {
    delete event;
    delete menuHandler;
    delete overworld;
    delete console;
    delete girly;
}

// Gets the instance of the game
Game* Game::getInstance() {
    if(!gameInstance) gameInstance = new Game;
    return gameInstance;
}

void Game::kill() {
    if(gameInstance) {
        delete gameInstance;
        gameInstance = NULL;
    }
}

void Game::displayLevel(int curLevelNbr) {
    if(event->keyIsPressed(sf::Keyboard::Return)) {
        state = GameState::INOVERWORLD;

        view.reset(ViewLayer::LEVEL);
        view.hide(ViewLayer::LEVEL);
        view.hide(ViewLayer::CONSOLE);
        view.show(ViewLayer::OVERWORLD);

    } else if (event->keyIsPressed(sf::Keyboard::M)) {
        state = GameState::INMENU;
        curLevel->pause();
        menuHandler->setNextState(GameState::INLEVEL);
        view.show(ViewLayer::MENU);
    }
    // testing purposes
    else if (event->keyIsPressed(sf::Keyboard::C)) {
        state = GameState::INCONSOLE;
        curLevel->pause();
        console->setNextState(GameState::INLEVEL);
        view.show(ViewLayer::CONSOLE);
    } else {
        curLevel->live(event, frameClock.restart());
    }
}

void Game::loadLevel(int levelNbr) {
    if(curLevel) {
        delete curLevel;
        curLevel = NULL;
    }
    state = GameState::INLEVEL;
    curLevelNbr = levelNbr;
    curLevel = new Level("assets/levels/level2.txt", LevelEnv::FIELD);
    view.addView(ViewLayer::LEVEL, curLevel);
}

void Game::handleOverworld() {
    sf::Time time = frameClock.restart();
    if (event->keyIsPressed(sf::Keyboard::N)) {
        overworld->evolve();
    }

    if(!overworld->getElodie()->hasToMove()) {
        overworld->getElodie()->noMoves();
        overworld->getElodie()->stand();
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
        view.show(ViewLayer::LEVEL);
    } else if (event->keyIsPressed(sf::Keyboard::M)) {
        state = GameState::INMENU;
        menuHandler->setNextState(GameState::INOVERWORLD);
        view.show(ViewLayer::MENU);
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
        state = menuHandler->execute();
        if (state == GameState::INOVERWORLD) {
            view.hide(ViewLayer::MENU);
            view.show(ViewLayer::OVERWORLD);
        }
    }
    if(event->keyIsPressed(sf::Keyboard::M)) {
        state = menuHandler->getNextState();
        if (state == GameState::INOVERWORLD) {
            view.hide(ViewLayer::MENU);
            view.show(ViewLayer::OVERWORLD);
        } else if (state == GameState::INLEVEL) {
            if(curLevel) {
                state = GameState::INLEVEL;
                view.hide(ViewLayer::MENU);
                view.show(ViewLayer::LEVEL);
                frameClock.restart();
                curLevel->play();
            } else {
                std::cerr << "Must display level but not initialized." << std::endl;
            }
        }
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
                frameClock.restart();
                curLevel->play();
            } else {
                std::cerr << "Must display level but not initialized." << std::endl;
            }
        }
    }

}

Console* Game::getConsole() {
    return console;
}

void Game::run() {
    sf::RenderWindow* window = view.getWindow();
    view.show(ViewLayer::MENU);
    while (window->isOpen()) {
        event->listening();

        if (event->keyIsHold(sf::Keyboard::Escape)) {
            window->close();
        }

        if (event->keyIsPressed(sf::Keyboard::F1)) {
            sf::Image screen = window->capture();
            screen.saveToFile("screenshot.jpg");
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
            displayLevel(curLevelNbr);
            break;
        case GameState::INOVERWORLD:
            handleOverworld();
            break;
        case GameState::INMENU:
            displayMenu();
            break;
        case GameState::INCONSOLE:
            displayConsole();
            break;
        case GameState::EXIT:
            exit();
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

void Game::exit() {
    view.getWindow()->close();
}

void Game::setState(GameState state) {
    this->state = state;
}
