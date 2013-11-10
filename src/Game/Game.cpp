#include "Game.h"

Game::Game()
{
    this->event = new EventHandler(this->view.getWindow());
}

Game::~Game()
{
    delete event;
}

void Game::init()
{
    // ???
}

void Game::run()
{
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

    while (window->isOpen())
    {
        event->listening();

        if (event->keyIsHold(esc))
        {
            window->close();
        }

        if (event->keyIsPressed(sf::Keyboard::N))
        {
            overworld.evolve();
        }

        if (event->keyIsPressed(sf::Keyboard::F1))
        {
            sf::Image screen = window->capture();
            screen.saveToFile("screenshot.jpg");
        }

        /*
        if (event->keyIsReleased(movement) && !event->keyIsHold(movement))
            animatedSprite.setAnimation(standingAnimation);
        if (event->keyIsPressed(movement) && !event->keyIsHold(movement))
            animatedSprite.setAnimation(walkingAnimation);
        */

        if(toMove <= 0)
        {
            toMove = 0;
            noMoves();
            overworld.getElodie()->stand();
        }

        if(isMoving())
        {
            overworld.getElodie()->walk();
            if (goingDown)
            {
                toMove -= speed;
                overworld.getElodieSprite()->move(0, speed);
            }
            else if (goingLeft)
            {
                toMove -= speed;
                overworld.getElodieSprite()->move(-speed, 0);
            }
            else if (goingRight)
            {
                toMove -= speed;
                overworld.getElodieSprite()->move(+speed, 0);
            }
            else if (goingUp)
            {
                toMove -= speed;
                overworld.getElodieSprite()->move(0, -speed);
            }
            else
            {
                noMoves();
            }
        }
        else if (event->keyIsHold(sf::Keyboard::Down))
        {
            toMove = overworld.moveDown();
            if(toMove > 0)
            {
                goingDown = true;
            }
        }
        else if (event->keyIsHold(sf::Keyboard::Up))
        {
            toMove = overworld.moveUp();
            if(toMove > 0)
            {
                goingUp = true;
            }
        }
        else if (event->keyIsHold(sf::Keyboard::Left))
        {
            toMove = overworld.moveLeft();
            if(toMove > 0)
            {
                goingLeft = true;
            }
        }
        else if (event->keyIsHold(sf::Keyboard::Right))
        {
            toMove = overworld.moveRight();
            if(toMove > 0)
            {
                goingRight = true;
            }
        }

        overworld.getElodieSprite()->update(frameClock.restart());

        view.addDrawable(overworld.getCurrentSprite());

        view.addDrawable(overworld.getElodieSprite());

        view.addDrawable(overworld.getPath());

        view.draw();
    }
}

bool Game::isMoving()
{
    return goingDown or goingLeft or goingRight or goingUp;
}

void Game::noMoves()
{
    goingDown = false;
    goingLeft = false;
    goingRight = false;
    goingUp = false;
}
