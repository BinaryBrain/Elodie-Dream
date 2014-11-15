#include "Girly.h"

Girly::Girly(GameView& gameView) : Displayable(gameView)
{
    float viewX = gameView.getSizeX();
    float viewY = gameView.getSizeY();

    gameView.addView(ViewLayer::GIRLY, this);
    filter.setSize(sf::Vector2f(viewX, viewY));
    filter.setFillColor(sf::Color(0xFF, 0x14, 0x93, 0x7f));
    filter.setPosition(0, 0);
}

Girly::~Girly()
{
    //dtor
}

void Girly::display()
{
    gameView.addDrawable(ViewLayer::GIRLY, &filter);
}
