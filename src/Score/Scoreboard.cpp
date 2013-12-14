#include "Scoreboard.h"

Scoreboard::Scoreboard(GameView* view) : Displayable(view) {
    ScoreManager* scoreManager = ScoreManager::getInstance();

    float viewX(WINDOW_WIDTH);
    float viewY(WINDOW_HEIGHT);

    rect.setSize(sf::Vector2f(viewX, viewY));
    rect.setFillColor(sf::Color(0x00, 0x00, 0x00, 0xFF));
    rect.setPosition(0, 0);

    int damages = scoreManager->getLastSavedScore().damage;
    int enemiesKilled = 3;

    damagesTakenText.setString("Damages taken: " + Utils::itos(damages));
    damagesTakenText.setFont(globalFont);
    damagesTakenText.setCharacterSize(SCORES_CHAR_SIZE);
    damagesTakenText.setPosition(viewX/2-damagesTakenText.getLocalBounds().width/2, SCORES_STARTY);

    view->addView(ViewLayer::SCORE, this);
}

Scoreboard::~Scoreboard() {

}

void Scoreboard::display() {
    ScoreManager* scoreManager = ScoreManager::getInstance();
    float viewX(WINDOW_WIDTH);
    float viewY(WINDOW_HEIGHT);

    int damages = scoreManager->getLastSavedScore().damage;
    int enemiesKilled = 3;

    damagesTakenText.setString("Damages taken: " + Utils::itos(damages));
    damagesTakenText.setPosition(viewX/2-damagesTakenText.getLocalBounds().width/2, SCORES_STARTY);

    gameView->addDrawable(ViewLayer::SCORE, &rect);
    gameView->addDrawable(ViewLayer::SCORE, &damagesTakenText);
}
