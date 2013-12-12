#include "Death.h"

Death::Death(GameView * view):Displayable(view) {
    float viewX(gameView->getWindow()->getSize().x);
    float viewY(gameView->getWindow()->getSize().y);

    font = new sf::Font();
    font->loadFromFile("assets/fonts/pf_tempesta_seven/pf_tempesta_seven.ttf");

    text = new sf::Text("You woke up ... ", *font);
    text->setCharacterSize(30);
    text->setPosition((viewX-text->getLocalBounds().width)/2, (viewY-text->getLocalBounds().height)/2);

    rect.setSize(sf::Vector2f(viewX, viewY));
    rect.setFillColor(sf::Color(0x00, 0x00, 0x00, 0xFF));
    rect.setPosition(0, 0);
}

Death::~Death() {
    delete font;
    delete text;
}

void Death::display() {

    gameView->addDrawable(ViewLayer::DEATH, &rect);
    gameView->addDrawable(ViewLayer::DEATH, text);
}
