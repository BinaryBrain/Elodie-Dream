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
    GameState lastUsableState = GameState::INMENU;
    ScoreManager* scoreManager = NULL;
    sf::Text levelScore;
    sf::Text levelBonus;
    sf::Sprite bonusSprite;
};

#endif // SCOREBOARD_H
