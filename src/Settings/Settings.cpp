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

bool Settings::isOpened() {
    return opened;
}

void Settings::draw(GameView* view) {
    std::vector<sf::Text*> options;
    options.push_back(new sf::Text("Volume", *font));
    options.push_back(new sf::Text("Language", *font));


    for(unsigned int i(0); i < options.size(); ++i) {
        options[i]->setPosition(100,100+50*i);
        options[i]->setCharacterSize(30);
        options[i]->setStyle(sf::Text::Bold);
        options[i]->setColor(sf::Color::Magenta);
        view->addDrawable(options[i]);
    }
}
