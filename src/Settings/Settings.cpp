#include <vector>
#include "Settings.h"

Settings::Settings() {
    opened = false;
    font = new sf::Font();
    font->loadFromFile("assets/fonts/arial.ttf");
}

Settings::~Settings() {
    //dtor
}

void Settings::open() {
    if(!opened) {
        opened = true;
    }
}

void Settings::close() {
    if(opened) {
        opened = false;
    }
}

void Settings::changeState() {
    opened = !opened;
}

void Settings::draw(GameView* view) {
    sf::Text* txt = new sf::Text("Volume", *font);
    txt->setString("hello");
    txt->setPosition(50,50);
    txt->setCharacterSize(30);
    txt->setStyle(sf::Text::Bold);
    txt->setColor(sf::Color::Magenta);
    view->addDrawable(txt);
}

bool Settings::isOpened() {
    return opened;
}
