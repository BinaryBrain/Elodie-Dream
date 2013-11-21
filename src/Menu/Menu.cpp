#include "Menu.h"
#include <SFML/Graphics.hpp>

Menu::Menu() {
    font = new sf::Font();
    font->loadFromFile("assets/fonts/arial.ttf");

    texture.loadFromFile("assets/img/sprites/menu/selector.png");
    texture.setSmooth(true);
    selector.setTexture(texture);

    index = 0;

    options.push_back(new sf::Text("New Game", *font));
    options.push_back(new sf::Text("Load", *font));
    options.push_back(new sf::Text("Settings", *font));
    options.push_back(new sf::Text("Quit", *font));
}

Menu::~Menu() {

}

void Menu::draw(GameView* view) {

    for(unsigned int i(0); i < options.size(); ++i) {
        options[i]->setPosition(200, 100+50*i);
        options[i]->setCharacterSize(30);
        options[i]->setStyle(sf::Text::Bold);
        options[i]->setColor(sf::Color::Magenta);
        view->addDrawable(options[i]);
    }

    selector.setPosition(150, 5+100+50*index);
    selector.setScale(0.25, 0.25);
    view->addDrawable(&selector);
}

void Menu::incIndex() {
    if (index == options.size()-1) index = 0;
    else ++index;
}

void Menu::decIndex() {
   if (index == 0) index = options.size()-1;
    else --index;
}

int Menu::getIndex() {
    return index;
}
