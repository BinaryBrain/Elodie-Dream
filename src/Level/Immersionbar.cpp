#include "Immersionbar.h"

ImmersionBar::ImmersionBar()
{
    outLine.setSize(sf::Vector2f(IMMERSION_BAR_W, IMMERSION_BAR_H));
    outLine.setFillColor(sf::Color::Transparent);
    outLine.setOutlineColor(IMMERSION_BAR_OUTLINE);
    outLine.setOutlineThickness(IMMERSION_BAR_OUTLINE_THICKNESS);
    outLine.setPosition(IMMERSION_BAR_X, IMMERSION_BAR_Y);

    filling.setFillColor(IMMERSION_BAR_FILL);
    filling.setOutlineColor(sf::Color::Transparent);
    filling.setOutlineThickness(IMMERSION_BAR_OUTLINE_THICKNESS);
    filling.setPosition(IMMERSION_BAR_X, IMMERSION_BAR_Y);
}

ImmersionBar::~ImmersionBar()
{
    //dtor
}

void ImmersionBar::display(GameView* view) {
    filling.setSize(sf::Vector2f(2*level, IMMERSION_BAR_H));
    view->addDrawable(ViewLayer::IMMERSIONBAR, &outLine);
    view->addDrawable(ViewLayer::IMMERSIONBAR, &filling);
}

void ImmersionBar::setLevel(int level)
{
    this->level = level;
}
