#ifndef GAME_H
#define GAME_H

#include <string>

#include "../Level/Level.h"
#include "../Map/Mapper.h"
#include "../FileHandler/FileHandler.h"
#include "../Overworld/Overworld.h"
#include "../EventHandler/EventHandler.h"
#include "GameView.h"

class Game {
public:
    Game();
    virtual ~Game();

    void init();
    void draw();
    void run();

    Level loadLevel(std::string filename);
protected:
private:
    EventHandler* m_event;

    Overworld m_overworld;
    sf::Clock m_frameClock;

    GameView m_view;

    bool m_inLevel = false;
};

#endif // GAME_H
