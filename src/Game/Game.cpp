#include "Game.h"

// Initialisation of the sinlgeton to NULL
Game* Game::gameInstance = NULL;

Game::Game() {
    event = new EventHandler(view.getWindow());

    //temporary there for testing
    NewGameItem* newGame = new NewGameItem("New game");
    QuitItem* quit = new QuitItem("Quit");
    EnglishItem* english = new EnglishItem("English");

    title = new Menu("Back");
    Menu* loadGame = new Menu("Load game");
    Menu* settings = new Menu("Settings");

    title->addItem(newGame);
    title->addItem(loadGame);
    title->addItem(settings);
    title->addItem(quit);

    settings->addItem(english);

}

Game::~Game() {
    delete event;
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

void Game::init() {
    // ???
}

void Game::displayLevel(int curLevelNbr) {
    if(event->keyIsPressed(sf::Keyboard::Return)) {
        state = GameState::INOVERWORLD;

        if(curLevel) {
            delete curLevel;
        }
    }
    else {
        curLevel->live(event, frameClock.restart());
        curLevel->draw(&view);
    }
}

void Game::loadLevel(int levelNbr) {
    state = GameState::INLEVEL;
    curLevelNbr = levelNbr;
    //curLevel = new Level("assets/levels/alltiles.txt");
    curLevel = new Level("assets/levels/level1.txt");
}

void Game::handleOverworld() {

    if (event->keyIsPressed(sf::Keyboard::N)) {
        overworld.evolve();
    }

    if(!overworld.getElodie()->hasToMove()) {
        overworld.getElodie()->noMoves();
        overworld.getElodie()->stand();
    }

    if(overworld.getElodie()->isMoving()) {
        overworld.getElodie()->overworldMove();
    } else if (event->keyIsHold(sf::Keyboard::Down)) {
        overworld.getElodie()->setDistanceToMove(overworld.moveDown());
        if(overworld.getElodie()->hasToMove()) {
            overworld.getElodie()->setWalkDown();
        }
    } else if (event->keyIsHold(sf::Keyboard::Up)) {
        overworld.getElodie()->setDistanceToMove(overworld.moveUp());
        if(overworld.getElodie()->hasToMove()) {
            overworld.getElodie()->setWalkUp();
        }
    } else if (event->keyIsHold(sf::Keyboard::Left)) {
        overworld.getElodie()->setDistanceToMove(overworld.moveLeft());
        if(overworld.getElodie()->hasToMove()) {
            overworld.getElodie()->setWalkLeft();
        }
    } else if (event->keyIsHold(sf::Keyboard::Right)) {
        overworld.getElodie()->setDistanceToMove(overworld.moveRight());
        if(overworld.getElodie()->hasToMove()) {
            overworld.getElodie()->setWalkRight();
        }
    } else if (event->keyIsPressed(sf::Keyboard::Return)) {
        loadLevel(0);
    } else if (event->keyIsPressed(sf::Keyboard::M)) {
        state = GameState::INMENU;
    }

    overworld.getElodie()->update(frameClock.restart());

    overworld.drawOnView(&view);

    view.reset();
}

void Game::displayMenu() {
    title->draw(&view);

    if (event->keyIsPressed(sf::Keyboard::Down)) title->incIndex();
    if (event->keyIsPressed(sf::Keyboard::Up)) title->decIndex();
    if (event->keyIsPressed(sf::Keyboard::Return)) state = title->getCurrentItem();
}

void Game::run() {
    // TODO Shouldn't be here
    std::vector<int> esc;
    esc.push_back(sf::Keyboard::Escape);
    esc.push_back(sf::Keyboard::LShift);
    std::vector<int> movement;
    movement.push_back(sf::Keyboard::Left);
    movement.push_back(sf::Keyboard::Right);
    movement.push_back(sf::Keyboard::Up);
    movement.push_back(sf::Keyboard::Down);

    sf::RenderWindow* window = view.getWindow();

    while (window->isOpen()) {
        event->listening();

        if (event->keyIsHold(esc)) {
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

        switch(state) {
        case GameState::INLEVEL:
            displayLevel(curLevelNbr);
            break;
        case GameState::INOVERWORLD:
            handleOverworld();
            break;
        case GameState::EXIT:
            exit();
            break;
        default :
            displayMenu();
        }

        view.draw();
    }
}

void Game::exit() {
    view.getWindow()->close();
}

void Game::setState(GameState state){
    this->state = state;
}
