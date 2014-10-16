#ifndef STATSBOARD_H
#define STATSBOARD_H

#include "../const.h"
#include "../font.h"
#include "../Utils/Utils.h"
#include "../Displayable/Displayable.h"
#include "../Game/GameView.h"
#include "ScoreManager.h"


class StatsBoard : public Displayable {
public:
    StatsBoard(GameView* gameView);
    virtual ~StatsBoard();

    void display();
    void prepareText();

private:
    sf::RectangleShape background;
    sf::Text levelsText;

    std::vector< std::pair<sf::Text, sf::Text> > categoriesText;

    std::pair<sf::Text, sf::Text> createCategoryText(float x, float y, std::string title, std::vector<int> levelDatas);
};

#endif // STATSBOARD_H
