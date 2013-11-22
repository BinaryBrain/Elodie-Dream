#include "Game.h"

Game::Game() {
    event = new EventHandler(view.getWindow());
    //temporary there for testing
    std::vector<std::string> menuTitles {"New Game", "Load", "Settings", "Quit"};
    titleMenu.setTitles(menuTitles);
    std::vector<std::string> settingsTitles {"Language", "Back"};
    settingsMenu.setTitles(settingsTitles);
}

Game::~Game() {
    delete event;
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
        curLevel->draw(&view);
    }
}

void Game::loadLevel(int levelNbr) {
    state = GameState::INLEVEL;
    curLevelNbr = levelNbr;
    //curLevel = new Level("assets/levels/alltiles.txt");
    curLevel = new Level("assets/levels/level1.txt");
}

void Game::displayOverworld() {

    if (event->keyIsPressed(sf::Keyboard::N)) {
        overworld.evolve();
    }

    if(!overworld.getElodie()->hasToMove()) {
        overworld.getElodie()->noMoves();
        overworld.getElodie()->stand();
    }

    if(overworld.getElodie()->isMoving()) {
        overworld.getElodie()->move();
    } else if (event->keyIsHold(sf::Keyboard::Down)) {
        overworld.getElodie()->setDistanceToMove(overworld.moveDown());
        if(overworld.getElodie()->hasToMove()) {
            overworld.getElodie()->walkDown();
        }
    } else if (event->keyIsHold(sf::Keyboard::Up)) {
        overworld.getElodie()->setDistanceToMove(overworld.moveUp());
        if(overworld.getElodie()->hasToMove()) {
            overworld.getElodie()->walkUp();
        }
    } else if (event->keyIsHold(sf::Keyboard::Left)) {
        overworld.getElodie()->setDistanceToMove(overworld.moveLeft());
        if(overworld.getElodie()->hasToMove()) {
            overworld.getElodie()->walkLeft();
        }
    } else if (event->keyIsHold(sf::Keyboard::Right)) {
        overworld.getElodie()->setDistanceToMove(overworld.moveRight());
        if(overworld.getElodie()->hasToMove()) {
            overworld.getElodie()->walkRight();
        }
    } else if (event->keyIsPressed(sf::Keyboard::Return)) {
        loadLevel(0);
    } else if (event->keyIsPressed(sf::Keyboard::M)) {
        state = GameState::INMENU;
    }

    overworld.getElodie()->update(frameClock.restart());

    view.addDrawable(overworld.getCurrentSprite());
    view.addDrawable(overworld.getElodie()->getSprite());
    view.addDrawable(overworld.getPath());
}

void Game::displayMenu() {
    titleMenu.draw(&view);

    if (event->keyIsPressed(sf::Keyboard::Down)) titleMenu.incIndex();
    if (event->keyIsPressed(sf::Keyboard::Up)) titleMenu.decIndex();

    if (event->keyIsPressed(sf::Keyboard::Return)) {
        std::string option = titleMenu.getTitleKey();
        std::cout << "Title key : " << option << std::endl;
        if (option == "New Game") state = GameState::INOVERWORLD;
        if (option == "Settings") settingsMenu.open();
        if (option == "Quit") view.getWindow()->close();
    }
}

void Game::displaySettings() {
    settingsMenu.draw(&view);

    // Make something here so that the iputs are not used by the view behind too
    // Infinite loop , or nothing special if in a different state

    if (event->keyIsPressed(sf::Keyboard::Down)) settingsMenu.incIndex();
    if (event->keyIsPressed(sf::Keyboard::Up)) settingsMenu.decIndex();
    if (event->keyIsPressed(sf::Keyboard::Return)) {
        std::string option = titleMenu.getTitleKey();
        std::cout << "Title key : " << option << std::endl;
        if (option == "Back") settingsMenu.close();
    }

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
            displayOverworld();
            break;
        default :
            displayMenu();
        }

        /*if (event->mouseIsPressed(sf::Keyboard::O)) {
            settingsMenu.open();
        }

        if(settingsMenu.isOpened()) {
            drawSettings();
        }*/

        view.draw();
    }
}
