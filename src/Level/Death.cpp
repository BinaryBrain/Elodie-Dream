#include "Death.h"

Death::Death(GameView* view):Displayable(view)
{
    //ctor
}

Death::~Death()
{
    //dtor
}

void Death::display() {
    float viewX(gameView->getWindow()->getSize().x);
    float viewY(gameView->getWindow()->getSize().y);

    float dimX(viewX);
    float dimY(viewY);

    rect.setSize(sf::Vector2f(dimX, dimY));
    rect.setFillColor(sf::Color(0x00, 0x00, 0x00, 0xFF));
    rect.setPosition(0, 0);

    gameView->addDrawable(ViewLayer::DEATH, &rect);
}
