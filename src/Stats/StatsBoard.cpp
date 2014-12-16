#include "StatsBoard.h"

const float StatsBoard::MARGIN = 50;
const float StatsBoard::LINES_INTERSPACE = 15;
const int StatsBoard::CHAR_SIZE = 15;

StatsBoard::StatsBoard(GameView& gameView) : Displayable(gameView), statsManager(StatsManager::getInstance())
{
    float viewX(WINDOW_WIDTH);
    float viewY(WINDOW_HEIGHT);

    background.setSize(sf::Vector2f(viewX, viewY));
    background.setFillColor(sf::Color(0x00, 0x00, 0x00, 0xE0));
    background.setPosition(0, 0);

    gameView.addView(ViewLayer::STATS, this);
}

StatsBoard::~StatsBoard()
{

}

void StatsBoard::setLDL(const std::vector<int>& LDL)
{
    this->LDL = LDL;
}

void StatsBoard::setCurrentSubworld(int curSubworld)
{
    this->curSubworld = curSubworld;
}

void StatsBoard::display()
{
    gameView.addDrawable(ViewLayer::STATS, &background);

    for (size_t i = 0; i < allTexts.size(); ++i)
    {
        gameView.addDrawable(ViewLayer::STATS, &(allTexts[i]));
    }
}

void StatsBoard::prepareText()
{
    levelsPerSubworld = ScoreManager::getInstance().getLevelsPerSubworld();

    allTexts.clear();

    // Levels (Tutorial, Level 1, ...)
    createLevelTexts(MARGIN, MARGIN + LINES_INTERSPACE);

    // Categories (points, boni, ...)
    createAllCategoriesTexts();

    // More stats
    createMoreStats();
}

void StatsBoard::createLevelTexts(float beginX, float beginY)
{
    float y = beginY;

    int lastSubDisc = LDL[0];
    int lastLvlDisc = LDL[1];
    int limitToDisplay = levelsPerSubworld[curSubworld];

    for (int i = 0; i < limitToDisplay; i++)
    {
        if (curSubworld != lastSubDisc || i <= lastLvlDisc)
        {
            sf::Text levelText;
            std::vector<int> level = {curSubworld, i};

            levelText.setFont(globalFont);
            levelText.setCharacterSize(CHAR_SIZE);
            levelText.setString(SaveHandler::computeLevelName(level));
            levelText.setPosition(beginX, y + levelText.getLocalBounds().height);
            y += levelText.getLocalBounds().height + LINES_INTERSPACE;
            allTexts.push_back(levelText);
        }
    }
}

void StatsBoard::createAllCategoriesTexts()
{
    std::vector< std::vector< std::map<std::string, int> > > datas = ScoreManager::getInstance().get2DVectMapDatas();
    std::vector<std::string> titles;
    std::vector<std::string> keys;

    titles.push_back("Points");
    titles.push_back("Boni");
    titles.push_back("Damages taken");
    titles.push_back("Enemies killed");
    titles.push_back("Largest killing spree");

    keys.push_back(Score::TOTALPOINTS_KEY);
    keys.push_back(Score::BONI_KEY);
    keys.push_back(Score::DAMAGESTAKEN_KEY);
    keys.push_back(Score::ENEMIESKILLED_KEY);
    keys.push_back(Score::LARGESTKILLINGSPREE_KEY);

    std::vector< std::vector<int> > categories(titles.size());

    int lastSubDisc = LDL[0];
    int lastLvlDisc = LDL[1];
    int limitToDisplay = levelsPerSubworld[curSubworld];

    // for each level, store its values in the right category
    for (int i = 0; i < limitToDisplay; ++i)
    {
        if (curSubworld != lastSubDisc || i <= lastLvlDisc)
        {
            for (size_t j = 0; j < titles.size(); ++j)
            {
                categories[j].push_back(datas[curSubworld][i][keys[j]]);
            }
        }
    }

    float startX = MARGIN*2 + findLargestTextWidth(); // findLargestSize() will search max text width among the texts existing (i.e. the levelTexts)
    float categoryWidth = (gameView.getSizeX() - startX)/categories.size();

    for (size_t i = 0; i < titles.size(); ++i)
    {
        createCategoryTexts(startX +  categoryWidth*i, MARGIN, titles[i], categories[i]);
    }
}

void StatsBoard::createCategoryTexts(float beginX, float beginY, const std::string& title, const std::vector<int>& datas)
{
    sf::Text titleText;
    titleText.setFont(globalFont);
    titleText.setCharacterSize(CHAR_SIZE);
    titleText.setString(title);
    titleText.setPosition(beginX,beginY);
    allTexts.push_back(titleText);

    float titleWidth = titleText.getLocalBounds().width;
    float titleHeight = titleText.getLocalBounds().height;
    float y = beginY + titleHeight + LINES_INTERSPACE;

    for (size_t i = 0; i < datas.size(); ++i)
    {
        sf::Text t;
        t.setFont(globalFont);
        t.setCharacterSize(CHAR_SIZE);
        t.setString(Utils::itos(datas[i]));

        float x = beginX + titleWidth/2 - t.getLocalBounds().width/2;
        t.setPosition(x,y);
        y += t.getLocalBounds().height + LINES_INTERSPACE;
        allTexts.push_back(t);
    }
}

void StatsBoard::createMoreStats()
{
    sf::Text& lastText = allTexts[allTexts.size() - 1];
    float x = MARGIN;
    float y = lastText.getPosition().y + lastText.getLocalBounds().height + MARGIN;
    std::vector< std::pair<std::string, int>> namesValues = statsManager.getLabelledValues();

    for (size_t i = 0; i < namesValues.size(); ++i)
    {
        sf::Text t;
        t.setFont(globalFont);
        t.setCharacterSize(CHAR_SIZE);
        t.setString(namesValues[i].first + ": " + Utils::itos(namesValues[i].second));
        t.setPosition(x, y);

        y += t.getLocalBounds().height + LINES_INTERSPACE;
        allTexts.push_back(t);
    }
}

float StatsBoard::findLargestTextWidth()
{
    float maxWidth = 0;
    for (size_t i = 0; i < allTexts.size(); ++i)
    {
        float width = allTexts[i].getLocalBounds().width;
        if (maxWidth < width)
        {
            maxWidth = width;
        }
    }
    return maxWidth;
}
