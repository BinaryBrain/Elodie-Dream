#include "Game.h"

Game::Game() {
    event = new EventHandler(view.getWindow());
}

Game::~Game() {
    delete event;
}

void Game::init() {
    // ???
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

    Level level("assets/levels/alltiles.txt");

    sf::RenderWindow* window = view.getWindow();

    while (window->isOpen()) {
        event->listening();

        if (event->keyIsHold(esc)) {
            window->close();
        }

        if (event->keyIsPressed(sf::Keyboard::N)) {
            overworld.evolve();
        }

        if (event->keyIsPressed(sf::Keyboard::F1)) {
            sf::Image screen = window->capture();
            screen.saveToFile("screenshot.jpg");
        }

        if (event->mouseIsPressed(sf::Mouse::Left)) {
            eventMouse leftClick(event->mouseInfoPressed(sf::Mouse::Left));
            std::cout << "Mouse pos : (" << leftClick.x << "; " << leftClick.y << ")" << std::endl;
        }

        if (event->mouseIsWheeled())
            std::cout << "Wheeeee " << event->mouseIsWheeled() << std::endl;
        /*
        if (event->keyIsReleased(movement) && !event->keyIsHold(movement))
            animatedSprite.setAnimation(standingAnimation);
        if (event->keyIsPressed(movement) && !event->keyIsHold(movement))
            animatedSprite.setAnimation(walkingAnimation);
        */

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
        }

        if (event->keyIsPressed(sf::Keyboard::Return)) {
            inLevel = !inLevel;
        }

        if (inLevel) {
            level.draw(&view);
        } else {
            overworld.getElodie()->update(frameClock.restart());

            view.addDrawable(overworld.getCurrentSprite());
            view.addDrawable(overworld.getElodie()->getSprite());
            view.addDrawable(overworld.getPath());
        }

        if (event->keyIsPressed(sf::Keyboard::M)) {
            menu.changeState();
        }
        if(menu.isOpened()) {
            menu.draw(&view);
        }

        view.draw();
    }
}
