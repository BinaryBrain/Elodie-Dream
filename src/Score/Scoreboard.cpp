#include "Scoreboard.h"

Scoreboard::Scoreboard(GameView* view) : Displayable(view) {
    scoreManager = ScoreManager::getInstance();

    font = new sf::Font();
    font->loadFromFile("assets/fonts/pf_tempesta_seven/pf_tempesta_seven.ttf");

    levelScore = new sf::Text("empty", *font);
    levelScore->setCharacterSize(20);

    levelBonus = new sf::Text("empty", *font);
    levelBonus->setCharacterSize(30);

    texture.loadFromFile("assets/img/sprites/bonus/sprite.png");
    bonusSprite.setTexture(texture);

    /*float midEloX = (elo.getLocalBounds().width*GAMEOVER_ELOSCALE)/2;
    float midEloY = (elo.getLocalBounds().height*GAMEOVER_ELOSCALE)/2;
    float topElo = midY - midEloY;
    float botElo = midY + midEloY;
    elo.setPosition(midX - midEloX, midY - midEloY);

    oh->setPosition(midX - oh->getLocalBounds().width/2, topElo - GAMEOVER_INTERSPACE);

    wokeUp->setPosition(midX - wokeUp->getLocalBounds().width/2, botElo + GAMEOVER_INTERSPACE);*/


    view->addView(ViewLayer::SCORE, this);
}

Scoreboard::~Scoreboard() {
    delete font;
    delete levelScore;
    delete levelBonus;
}

void Scoreboard::display() {
    GameState currentState = Game::getInstance()->getState();
    float midX = WINDOW_WIDTH/2;
    float midY = WINDOW_HEIGHT/2;
    if (currentState == GameState::INOVERWORLD) {
        lastUsableState = currentState;
        int currentLevel = Game::getInstance()->getOverworld()->getLevelToLoad();
        if (currentLevel >= 0) {
            //std::cout << "in" << std::endl;
            Score currentScore = scoreManager->getScore(currentLevel);

            delete levelScore;
            std::string scoreText("Score: ");
            scoreText.append("1");
            levelScore = new sf::Text(scoreText, *font);
            levelScore->setCharacterSize(20);
            levelScore->setColor(sf::Color(0x00, 0x00, 0x00, 0xFF));
            levelScore->setPosition(midX - levelScore->getLocalBounds().width/2, 20);
            gameView->addDrawable(ViewLayer::SCORE, levelScore);

            delete levelBonus;
            std::string bonusText("");
            bonusText.append("1");
            levelBonus = new sf::Text(bonusText, *font);
            levelBonus->setCharacterSize(20);
            levelBonus->setColor(sf::Color(0x00, 0x00, 0x00, 0xFF));
            levelBonus->setPosition(midX - (levelBonus->getLocalBounds().width + SCORE_OVERWORLD_SPRITE_SIZE + 5)/2 + SCORE_OVERWORLD_SPRITE_SIZE + 5, levelScore->getPosition().y + 30 + (SCORE_OVERWORLD_SPRITE_SIZE - levelBonus->getLocalBounds().height) / 2);
            gameView->addDrawable(ViewLayer::SCORE, levelBonus);

            bonusSprite.setScale(SCORE_OVERWORLD_SPRITE_SIZE / bonusSprite.getLocalBounds().width, SCORE_OVERWORLD_SPRITE_SIZE / bonusSprite.getLocalBounds().height);
            bonusSprite.setPosition(midX - (levelBonus->getLocalBounds().width + SCORE_OVERWORLD_SPRITE_SIZE + 5)/2, levelScore->getPosition().y + 30);
            gameView->addDrawable(ViewLayer::SCORE, &bonusSprite);
        }
    }
}
