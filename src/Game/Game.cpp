#include "Game.h"

Game::Game() {
    this->window = new sf::RenderWindow(sf::VideoMode(1280, 720), "Elodie's Dream: Quest for Poros", sf::Style::Default);
    this->event = new EventHandler(*window);
}

Game::~Game() {
    delete window;
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

    loadLevel("assets/levels/level1.txt");

    while (window->isOpen()) {
        event->listening();

        if (event->keyIsHold(esc))
            window->close();

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

        draw();
    }
}

// TODO Separate the View from the controller
void Game::draw() {
    window->clear(sf::Color(0x00, 0xFF, 0x00));
    window->draw(*overworld.getCurrentSprite());
    window->display();
}

void Game::loadLevel(std::string filename) {
    std::string level = FileHandler::getContent(filename);

    TileMap tiles;
    EntitieVector entities;

    Mapper::parse(level, tiles, entities);
}
