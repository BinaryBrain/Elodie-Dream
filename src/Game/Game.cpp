#include "Game.h"

Game::Game() {
    this->event = new EventHandler(this->view.getWindow());
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

    Level level("assets/levels/level1.txt");

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

        /*
        if (event->keyIsReleased(movement) && !event->keyIsHold(movement))
            animatedSprite.setAnimation(standingAnimation);
        if (event->keyIsPressed(movement) && !event->keyIsHold(movement))
            animatedSprite.setAnimation(walkingAnimation);

        if (event->keyIsHold(sf::Keyboard::Down))
            animatedSprite.move(0, +0.05);
        if (event->keyIsHold(sf::Keyboard::Up))
            animatedSprite.move(0, -0.05);
        if (event->keyIsHold(sf::Keyboard::Left))
            animatedSprite.move(-0.05, 0);
        if (event->keyIsHold(sf::Keyboard::Right))
            animatedSprite.move(+0.05, 0);

        animatedSprite.update(frameClock.restart());

        if(animatedSprite.getPosition().x > window.getSize().x) {
            animatedSprite.setPosition(-50, animatedSprite.getPosition().y);
        }
        */

        view.addDrawable(overworld.getCurrentSprite());
        view.draw();
    }
}
