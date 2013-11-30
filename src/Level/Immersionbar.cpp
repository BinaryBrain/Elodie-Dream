#include "Immersionbar.h"

ImmersionBar::ImmersionBar()
{
    outLine.setSize(sf::Vector2f(200, 15));
    outLine.setFillColor((sf::Color(0x00, 0x00, 0x00, 0x00)));
    outLine.setOutlineColor((sf::Color(0x31, 0x55, 0x48, 0xFF)));
    outLine.setOutlineThickness(2);
    outLine.setPosition(540, 50);
    filling.setFillColor((sf::Color(0x73, 0xC8, 0xA9, 0xFF)));
    filling.setOutlineColor((sf::Color(0x00, 0x00, 0x00, 0x00)));
    filling.setOutlineThickness(2);
    filling.setPosition(540, 50);
}

ImmersionBar::~ImmersionBar()
{
    //dtor
}

void ImmersionBar::display(GameView* view) {
    filling.setSize(sf::Vector2f(2*level, 15));
    view->addDrawable(ViewLayer::IMMERSIONBAR, &outLine);
    view->addDrawable(ViewLayer::IMMERSIONBAR, &filling);
}

void ImmersionBar::setLevel(int level)
{
    this->level = level;
}
