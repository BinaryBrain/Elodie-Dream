#ifndef STATSBOARD_H
#define STATSBOARD_H

#include "../const.h"
#include "../Displayable/Displayable.h"
#include "../Game/GameView.h"


class StatsBoard : public Displayable {
public:
    StatsBoard(GameView* view);
    virtual ~StatsBoard();

    void display();

private:
    sf::RectangleShape background;
};

#endif // STATSBOARD_H
