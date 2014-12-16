#ifndef STATSBOARD_H
#define STATSBOARD_H

#include "../font.h"
#include "../Utils/Utils.h"
#include "../Displayable/Displayable.h"
#include "../Game/GameView.h"
#include "../FileHandler/SaveHandler.h"
#include "../Score/ScoreManager.h"


class StatsBoard : public Displayable
{
public:
    static const float MARGIN;
    static const float LINES_INTERSPACE;
    static const int CHAR_SIZE;

    StatsBoard(GameView& gameView);
    virtual ~StatsBoard();

    void setLDL(const std::vector<int>& LDL);
    void setCurrentSubworld(int curSubworld);
    void display();
    void prepareText();

private:
    void createLevelTexts(float beginX, float beginY);
    void createAllCategoriesTexts();
    void createCategoryTexts(float beginX, float beginY, const std::string& title, const std::vector<int>& datas);
    void createMoreStats();
    float findLargestTextWidth();

    int curSubworld;
    std::vector<int> LDL;
    std::vector<int> levelsPerSubworld;
    sf::RectangleShape background;
    std::vector<sf::Text> allTexts;
    StatsManager& statsManager;
};

#endif // STATSBOARD_H
