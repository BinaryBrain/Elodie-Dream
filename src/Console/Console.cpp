#include "Console.h"

Console::Console() {
    font->loadFromFile("assets/fonts/pf_tempesta_seven/pf_tempesta_seven.ttf");
}

Console::~Console() {
    //dtor
}

void Console::addSentence(std::string sentence) {
    lines.push_back(sentence);
}

void Console::setContent(std::vector<std::string> lines) {
    this->lines = lines;
}

std::vector<std::string> Console::makeLines(std::string str) {
    std::vector<size_t> indexes = getStringIndexes(str, " ");
    indexes.insert(indexes.begin(), 0);

    sf::Text* text = new sf::Text("", *font);
    std::vector<std::string> lines;
    std::string buffer(" "); // tricky temporary space at the beginning :3

    for (unsigned int i(0); i<indexes.size(); ++i) {
        int length(indexes[i+1] - indexes[i]);
        buffer += str.substr(indexes[i], length);
        text->setString(buffer);
        std::string textString = text->getString();

        if (text->getLocalBounds().width/1.8 > sizeX) { // don't know why getLocalBounds() doesn't work :/
            lines.push_back(buffer);
            buffer = "";
        }
    }

    lines.push_back(buffer);

    delete text;
    return lines;
}

void Console::clear() {
    lines.clear();
}

void Console::display(GameView* view) {

    float viewX(view->getWindow()->getSize().x);
    float viewY(view->getWindow()->getSize().y);

    sizeX = viewX;
    sizeY = 200;

    float startX(viewX-sizeX);
    float startY(viewY-sizeY);

    sf::Text* text;

    background.setSize(sf::Vector2f(sizeX, sizeX));
    background.setOutlineColor(sf::Color::Black);
    background.setFillColor(sf::Color(0x00, 0x00, 0x00, 0x7f));
    background.setOutlineThickness(3);
    background.setPosition(startX, startY);

    view->addDrawable(ViewLayer::CONSOLE, &background);

    for(unsigned int i(0); i < lines.size(); ++i) {
        text = new sf::Text(lines[i], *font);
        text->setCharacterSize(15);
        text->setColor(sf::Color::White);
        text->setPosition(startX+50, startY+20+20*i);
        view->addDrawable(ViewLayer::CONSOLE, text);
    }
}

std::vector<size_t> Console::getStringIndexes(std::string str, std::string sub) {
    std::vector<size_t> indexes;
    size_t index = str.find(sub, 0);
    while(index != std::string::npos) { // npos: last element of a size_t
        indexes.push_back(index);
        index = str.find(sub,index+1);
    }
    return indexes;
}
