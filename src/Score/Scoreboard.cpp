#include "Scoreboard.h"

Scoreboard::Scoreboard(GameView* view) : Displayable(view) {
    ScoreManager* scoreManager = ScoreManager::getInstance();

    float viewX(gameView->getWindow()->getSize().x);
    float viewY(gameView->getWindow()->getSize().y);

    rect.setSize(sf::Vector2f(viewX, viewY));
    rect.setFillColor(sf::Color(0x00, 0x00, 0x00, 0xFF));
    rect.setPosition(0, 0);

    damagesTaken.setString("empty");
    damagesTaken.setFont(globalFont);
    damagesTaken.setCharacterSize(30);
    damagesTaken.setPosition(60,60);

    view->addView(ViewLayer::SCORE, this);
}

Scoreboard::~Scoreboard() {

}

void Scoreboard::display() {
    gameView->addDrawable(ViewLayer::SCORE, &rect);
    gameView->addDrawable(ViewLayer::SCORE, &damagesTaken);
}
