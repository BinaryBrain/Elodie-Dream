#include "Console.h"

Console::Console() {
    font->loadFromFile("assets/fonts/arial.ttf");
}

Console::~Console() {
    //dtor
}

void Console::addSentence(std::string sentence) {
    sentences.push_back(sentence);
}

void Console::setContent(std::vector<std::string> sentences) {
    this->sentences = sentences;
}

void Console::clear() {
    sentences.clear();
}

void Console::display(GameView* view) {

    float viewX(view->getWindow()->getSize().x);
    float viewY(view->getWindow()->getSize().y);

    float dimX(viewX);
    float dimY(200);

    float startX(viewX-dimX);
    float startY(viewY-dimY);

    sf::Text* text;

    background.setSize(sf::Vector2f(dimX, dimY));
    background.setOutlineColor(sf::Color::White);
    background.setFillColor((sf::Color(0x00, 0x00, 0x00, 0x7f)));
    background.setOutlineThickness(3);
    background.setPosition(startX, startY);

    view->addDrawable(ViewLayer::CONSOLE, &background);

    for(unsigned int i(0); i < sentences.size(); ++i) {
        text = new sf::Text(sentences[i], *font);
        text->setStyle(sf::Text::Bold);
        text->setCharacterSize(15);
        text->setColor(sf::Color::White);
        text->setPosition(startX+50, startY+20+20*i);
        view->addDrawable(ViewLayer::CONSOLE, text);
    }
}
