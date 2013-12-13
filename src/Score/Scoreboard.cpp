#include "Scoreboard.h"

Scoreboard::Scoreboard(GameView* view) : Displayable(view) {
    sf::Font font;
    sf::Texture texture;

    //scoreManager = ScoreManager::getInstance();

    font.loadFromFile("assets/fonts/pf_tempesta_seven/pf_tempesta_seven.ttf");

    levelScore.setString("empty");
    levelScore.setFont(font);
    levelScore.setCharacterSize(20);
    levelScore.setColor(sf::Color(0x00, 0x00, 0x00, 0xFF));

    levelBonus.setString("empty");
    levelBonus.setFont(font);
    levelBonus.setCharacterSize(30);
    levelBonus.setColor(sf::Color(0x00, 0x00, 0x00, 0xFF));

    texture.loadFromFile("assets/img/sprites/bonus/sprite.png");
    bonusSprite.setTexture(texture);

    //view->addView(ViewLayer::SCORE, this);
}

Scoreboard::~Scoreboard() {
}

void Scoreboard::display() {
    GameState currentState = Game::getInstance()->getState();
    float midX = WINDOW_WIDTH/2;
    float midY = WINDOW_HEIGHT/2;
    if (currentState == GameState::INOVERWORLD) {
        lastUsableState = currentState;
        int currentLevel = Game::getInstance()->getOverworld()->getLevelToLoad();
        if (currentLevel >= 0) {
            Score currentScore = scoreManager->getScore(currentLevel);

            //delete levelScore;
            std::string scoreText("Score: ");
            std::ostringstream oss;
            oss << currentScore.score;
            scoreText.append(oss.str());
            levelScore.setString(scoreText);
            levelScore.setPosition(midX - levelScore.getLocalBounds().width/2, 20);
            gameView->addDrawable(ViewLayer::SCORE, &levelScore);

            //delete levelBonus;
            oss.str("");
            oss << currentScore.bonus;
            std::string bonusText = oss.str();
            bonusText.append("/5");
            levelBonus.setString(bonusText);
            levelBonus.setPosition(midX - (levelBonus.getLocalBounds().width + SCORE_OVERWORLD_SPRITE_SIZE + 5)/2 + SCORE_OVERWORLD_SPRITE_SIZE + 5, levelScore.getPosition().y + 30 + (SCORE_OVERWORLD_SPRITE_SIZE - levelBonus.getLocalBounds().height) / 2);
            gameView->addDrawable(ViewLayer::SCORE, &levelBonus);

            bonusSprite.setScale(SCORE_OVERWORLD_SPRITE_SIZE / bonusSprite.getLocalBounds().width, SCORE_OVERWORLD_SPRITE_SIZE / bonusSprite.getLocalBounds().height);
            bonusSprite.setPosition(midX - (levelBonus.getLocalBounds().width + SCORE_OVERWORLD_SPRITE_SIZE + 5)/2, levelScore.getPosition().y + 30);
            gameView->addDrawable(ViewLayer::SCORE, &bonusSprite);
        }
    } else if (currentState == GameState::INLEVEL) {
        lastUsableState = currentState;

        Score currentScore = scoreManager->getCurrentScore();

        //delete levelScore;
        std::string scoreText("Score: ");
        std::ostringstream oss;
        oss << currentScore.score;
        scoreText.append(oss.str());
        levelScore.setString(scoreText);
        levelScore.setPosition(midX - levelScore.getLocalBounds().width/2, 20);
        gameView->addDrawable(ViewLayer::SCORE, &levelScore);

        //delete levelBonus;
        oss.str("");
        oss << currentScore.bonus;
        std::string bonusText = oss.str();
        bonusText.append("/5");
        levelBonus.setString(bonusText);
        levelBonus.setPosition(midX - (levelBonus.getLocalBounds().width + SCORE_OVERWORLD_SPRITE_SIZE + 5)/2 + SCORE_OVERWORLD_SPRITE_SIZE + 5, levelScore.getPosition().y + 30 + (SCORE_OVERWORLD_SPRITE_SIZE - levelBonus.getLocalBounds().height) / 2);
        gameView->addDrawable(ViewLayer::SCORE, &levelBonus);

        bonusSprite.setScale(SCORE_OVERWORLD_SPRITE_SIZE / bonusSprite.getLocalBounds().width, SCORE_OVERWORLD_SPRITE_SIZE / bonusSprite.getLocalBounds().height);
        bonusSprite.setPosition(midX - (levelBonus.getLocalBounds().width + SCORE_OVERWORLD_SPRITE_SIZE + 5)/2, levelScore.getPosition().y + 30);
        gameView->addDrawable(ViewLayer::SCORE, &bonusSprite);
    }
}
