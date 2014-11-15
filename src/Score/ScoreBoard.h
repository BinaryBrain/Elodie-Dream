#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include "../Displayable/Displayable.h"
#include "../Game/GameView.h"
#include "../Score/ScoreManager.h"
#include "../Utils/Utils.h"
#include "../const.h"
#include "../font.h"

#include <SFML/Audio.hpp>

class ScoreBoard : public Displayable
{
public:
    static const int CHAR_SIZE;
    static const float INTERSPACE;
    static const float STARTY;

    ScoreBoard(GameView& gameView);
    virtual ~ScoreBoard();

    void display();
    void prepareText();

private:
    sf::RectangleShape rect;
    sf::Text damagesTakenText;
    sf::Text enemiesKilledText;
    sf::Text pointsText;
    sf::Text boniText;
};

#endif // SCOREBOARD_H
