#include "Girly.h"

Girly::Girly(GameView* gameView) : Displayable(gameView) {
    //ctor
}

Girly::~Girly() {
    //dtor
}

void Girly::display() {
    float viewX(gameView->getWindow()->getSize().x);
    float viewY(gameView->getWindow()->getSize().y);

    float dimX(viewX);
    float dimY(viewY);

    filter.setSize(sf::Vector2f(dimX, dimY));
    filter.setFillColor(sf::Color(0xFF, 0x14, 0x93, 0x7f));
    filter.setPosition(0, 0);

    gameView->addDrawable(ViewLayer::GIRLY, &filter);
}
