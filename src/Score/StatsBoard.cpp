#include "StatsBoard.h"

StatsBoard::StatsBoard(GameView* gameView) : Displayable(gameView) {
    float viewX(WINDOW_WIDTH);
    float viewY(WINDOW_HEIGHT);

    background.setSize(sf::Vector2f(viewX, viewY));
    background.setFillColor(sf::Color(0x00, 0x00, 0x00, 0xE0));
    background.setPosition(0, 0);

    levelsText.setFont(globalFont);
    levelsText.setCharacterSize(STATS_CHAR_SIZE);

    gameView->addView(ViewLayer::STATS, this);
}

StatsBoard::~StatsBoard() {
    //dtor
}

void StatsBoard::display() {
    gameView->addDrawable(ViewLayer::STATS, &background);
    gameView->addDrawable(ViewLayer::STATS, &levelsText);

    for (size_t i = 0; i < categoriesText.size(); ++i) {
        gameView->addDrawable(ViewLayer::STATS, &(categoriesText[i].first));
        gameView->addDrawable(ViewLayer::STATS, &(categoriesText[i].second));
    }
}

void StatsBoard::prepareText() {
    categoriesText.clear();
    ScoreManager* scoreManager = ScoreManager::getInstance();

    std::vector< std::vector<int> > allDatas = scoreManager->getAllDatas();

    std::string levels = "\nTutorial\n";

    for (int i = 1; i <= LDL; ++i) {
        levels += "Level " + Utils::itos(i) + "\n";
    }

    levelsText.setString(levels);
    levelsText.setPosition(STATS_MARGIN, STATS_MARGIN);

    std::vector<std::string> titles;
    titles.push_back("Points");
    titles.push_back("Boni");
    titles.push_back("Damages taken");
    titles.push_back("Enemies killed");
    titles.push_back("Sheeps");
    titles.push_back("Magma cubes");
    titles.push_back("Bristles");

    std::vector< std::vector<int> > categories;
    for (size_t i = 0; i < titles.size(); ++i) {
        std::vector<int> tmp;
        categories.push_back(tmp);
    }

    // for each level, store in the right category its values
    for (int i = 0; i <= LDL; ++i) {
        for (size_t j = 0; j < titles.size(); ++j) {
            categories[j].push_back(allDatas[i][j+2]);
        }
    }

    float startX = STATS_MARGIN*2 + levelsText.getLocalBounds().width;
    for (size_t i = 0; i < titles.size(); ++i) {
        categoriesText.push_back(createCategoryText(startX + STATS_MARGIN*i +  STATS_WIDTH_CATEGORY*i, STATS_MARGIN, titles[i], categories[i]));
    }
}

std::pair<sf::Text, sf::Text> StatsBoard::createCategoryText(float x, float y, std::string title, std::vector<int> datas) {

    sf::Text titleText;
    sf::Text valuesText;

    std::string values = "\n";

    for (size_t i = 0; i < datas.size(); ++i) {
        values += Utils::itos(datas[i]) + "\n";
    }

    titleText.setString(title);
    titleText.setFont(globalFont);
    titleText.setCharacterSize(STATS_CHAR_SIZE);
    titleText.setPosition(x, y);

    valuesText.setString(values);
    valuesText.setFont(globalFont);
    valuesText.setCharacterSize(STATS_CHAR_SIZE);
    valuesText.setPosition(x, y);

    return std::make_pair(titleText, valuesText);
}

void StatsBoard::setLDL(int LDL) {
    this->LDL = LDL;
}
