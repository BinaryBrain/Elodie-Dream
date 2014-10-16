#include "StatsBoard.h"

StatsBoard::StatsBoard(GameView* view) : Displayable(view) {
    float viewX(WINDOW_WIDTH);
    float viewY(WINDOW_HEIGHT);

    background.setSize(sf::Vector2f(viewX, viewY));
    background.setFillColor(sf::Color(0x00, 0x00, 0x00, 0xF0));
    background.setPosition(0, 0);
}

StatsBoard::~StatsBoard() {
    //dtor
}

void StatsBoard::display() {
    gameView->addDrawable(ViewLayer::STATS, &background);
}
