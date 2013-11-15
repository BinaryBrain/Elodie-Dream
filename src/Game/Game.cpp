#include "Game.h"

Game::Game() {
    this->m_event = new EventHandler(this->m_view.getWindow());
}

Game::~Game() {
    delete m_event;
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

    sf::RenderWindow* window = m_view.getWindow();

    while (window->isOpen()) {
        m_event->listening();

        if (m_event->keyIsHold(esc)) {
            window->close();
        }

        if (m_event->keyIsPressed(sf::Keyboard::N)) {
            m_overworld.evolve();
        }

        if (m_event->keyIsPressed(sf::Keyboard::F1)) {
            sf::Image screen = window->capture();
            screen.saveToFile("screenshot.jpg");
        }

        if (m_event->mouseIsPressed(sf::Mouse::Left)) {
            eventMouse leftClick(m_event->mouseInfoPressed(sf::Mouse::Left));
            std::cout << "Mouse pos : (" << leftClick.x << "; " << leftClick.y << ")" << std::endl;
        }

        if (m_event->mouseIsWheeled())
            std::cout << "Wheeeee " << m_event->mouseIsWheeled() << std::endl;
        /*
        if (event->keyIsReleased(movement) && !event->keyIsHold(movement))
            animatedSprite.setAnimation(standingAnimation);
        if (event->keyIsPressed(movement) && !event->keyIsHold(movement))
            animatedSprite.setAnimation(walkingAnimation);
        */

        if(!m_overworld.getElodie()->hasToMove()) {
            m_overworld.getElodie()->noMoves();
            m_overworld.getElodie()->stand();
        }

        if(m_overworld.getElodie()->isMoving()) {
            m_overworld.getElodie()->move();
        } else if (m_event->keyIsHold(sf::Keyboard::Down)) {
            m_overworld.getElodie()->setDistanceToMove(m_overworld.moveDown());
            if(m_overworld.getElodie()->hasToMove()) {
                m_overworld.getElodie()->walkDown();
            }
        } else if (m_event->keyIsHold(sf::Keyboard::Up)) {
            m_overworld.getElodie()->setDistanceToMove(m_overworld.moveUp());
            if(m_overworld.getElodie()->hasToMove()) {
                m_overworld.getElodie()->walkUp();
            }
        } else if (m_event->keyIsHold(sf::Keyboard::Left)) {
            m_overworld.getElodie()->setDistanceToMove(m_overworld.moveLeft());
            if(m_overworld.getElodie()->hasToMove()) {
                m_overworld.getElodie()->walkLeft();
            }
        } else if (m_event->keyIsHold(sf::Keyboard::Right)) {
            m_overworld.getElodie()->setDistanceToMove(m_overworld.moveRight());
            if(m_overworld.getElodie()->hasToMove()) {
                m_overworld.getElodie()->walkRight();
            }
        }

        if (m_event->keyIsPressed(sf::Keyboard::Return)) {
            m_inLevel = !m_inLevel;
        }

        if (m_inLevel) {
            level.draw(&m_view);
        } else {
            m_overworld.getElodie()->update(m_frameClock.restart());

            m_view.addDrawable(m_overworld.getCurrentSprite());
            m_view.addDrawable(m_overworld.getElodie()->getSprite());
            m_view.addDrawable(m_overworld.getPath());
        }

        m_view.draw();
    }
}
