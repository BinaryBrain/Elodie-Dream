#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include "../Displayable/Displayable.h"
#include "../Game/Game.h"
#include "../Game/GameView.h"
#include "../Score/ScoreManager.h"
#include "../const.h"

#include <SFML/Audio.hpp>

class Scoreboard : public Displayable {
public:
    Scoreboard(GameView* view);
    virtual ~Scoreboard();

    void display();

private:
    sf::RectangleShape rect;
};

#endif // SCOREBOARD_H
