#include "StatsBoard.h"

StatsBoard::StatsBoard(GameView* gameView) : Displayable(gameView) {
    float viewX(WINDOW_WIDTH);
    float viewY(WINDOW_HEIGHT);

    background.setSize(sf::Vector2f(viewX, viewY));
    background.setFillColor(sf::Color(0x00, 0x00, 0x00, 0xE0));
    background.setPosition(0, 0);

    gameView->addView(ViewLayer::STATS, this);
}

StatsBoard::~StatsBoard() {
    //dtor
}

void StatsBoard::display() {
    gameView->addDrawable(ViewLayer::STATS, &background);
}
