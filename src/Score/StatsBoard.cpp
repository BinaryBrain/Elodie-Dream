#include "StatsBoard.h"

const float StatsBoard::MARGIN = 50;
const float StatsBoard::LINES_INTERSPACE = 15;
const int StatsBoard::CHAR_SIZE = 15;

StatsBoard::StatsBoard(GameView& gameView) : Displayable(gameView) {
    float viewX(WINDOW_WIDTH);
    float viewY(WINDOW_HEIGHT);

    background.setSize(sf::Vector2f(viewX, viewY));
    background.setFillColor(sf::Color(0x00, 0x00, 0x00, 0xE0));
    background.setPosition(0, 0);

    gameView.addView(ViewLayer::STATS, this);
}

StatsBoard::~StatsBoard() {

}

void StatsBoard::display() {
    gameView.addDrawable(ViewLayer::STATS, &background);

    for (size_t i = 0; i < categoriesTexts.size(); ++i) {
        gameView.addDrawable(ViewLayer::STATS, &(categoriesTexts[i]));
    }
}

void StatsBoard::prepareText() {
    categoriesTexts.clear();

    std::vector< std::vector<int> > allDatas = ScoreManager::getInstance().getAllDatas();
    std::vector<std::string> titles;
    titles.push_back("Points");
    titles.push_back("Boni");
    titles.push_back("Damages taken");
    titles.push_back("Enemies killed");
    titles.push_back("Largest killing spree");

    float x = MARGIN;
    float y = MARGIN + LINES_INTERSPACE;
    float maxWidth = 0;

    for (int i = 0; i <= LDL; i++) {
        sf::Text levelText;
        levelText.setFont(globalFont);
        levelText.setCharacterSize(CHAR_SIZE);
        levelText.setString(SaveHandler::computeLevelName(i));
        levelText.setPosition(x, y + levelText.getLocalBounds().height);

        float width = levelText.getLocalBounds().width;
        if (maxWidth < width) {
            maxWidth = width;
        }
        y += levelText.getLocalBounds().height + LINES_INTERSPACE;
        categoriesTexts.push_back(levelText);
    }

    std::vector< std::vector<int> > categories;
    for (size_t i = 0; i < titles.size(); ++i) {
        std::vector<int> tmp;
        categories.push_back(tmp);
    }

    // for each level, store in the right category its values
    for (int i = 0; i <= LDL; ++i) {
        for (size_t j = 0; j < titles.size(); ++j) {
            categories[j].push_back(allDatas[i][j+1]);
        }
    }

    float startX = MARGIN*2 + maxWidth;
    float categoryWidth = (gameView.getSizeX() - startX)/categories.size();

    for (size_t i = 0; i < titles.size(); ++i) {
        std::vector<sf::Text> texts = createCategoryTexts(startX +  categoryWidth*i, MARGIN, titles[i], categories[i]);
        for (size_t j = 0; j < texts.size(); ++j) {
            categoriesTexts.push_back(texts[j]);
        }
    }
}

std::vector<sf::Text> StatsBoard::createCategoryTexts(float beginX, float beginY, const std::string& title, const std::vector<int>& datas) {
    std::vector<sf::Text> texts;

    sf::Text titleText;
    titleText.setFont(globalFont);
    titleText.setCharacterSize(CHAR_SIZE);
    titleText.setString(title);
    titleText.setPosition(beginX,beginY);
    texts.push_back(titleText);

    float titleWidth = titleText.getLocalBounds().width;
    float titleHeight = titleText.getLocalBounds().height;
    float y = beginY + titleHeight + LINES_INTERSPACE;

    for (size_t i = 0; i < datas.size(); ++i) {
        sf::Text t;
        t.setFont(globalFont);
        t.setCharacterSize(CHAR_SIZE);
        t.setString(Utils::itos(datas[i]));

        float x = beginX + titleWidth/2 - t.getLocalBounds().width/2;
        t.setPosition(x,y);
        y += t.getLocalBounds().height + LINES_INTERSPACE;
        texts.push_back(t);
    }

    return texts;
}

void StatsBoard::setLDL(int LDL) {
    this->LDL = LDL;
}
