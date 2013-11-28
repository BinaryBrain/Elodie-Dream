#include "Girly.h"

Girly::Girly() {
    //ctor
}

Girly::~Girly() {
    //dtor
}

void Girly::display(GameView* view) {
    float viewX(view->getWindow()->getSize().x);
    float viewY(view->getWindow()->getSize().y);

    float dimX(viewX);
    float dimY(viewY);

    filter.setSize(sf::Vector2f(dimX, dimY));
    filter.setFillColor((sf::Color(0xFF, 0x14, 0x93, 0x7f)));
    filter.setPosition(0, 0);

    view->addDrawable(ViewLayer::GIRLY, &filter);
}
