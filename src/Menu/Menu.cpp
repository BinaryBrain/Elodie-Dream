#include "Menu.h"
#include <SFML/Graphics.hpp>

Menu::Menu() {
    font = new sf::Font();
    font->loadFromFile("assets/fonts/arial.ttf");
}

Menu::~Menu() {

}

void Menu::draw(GameView* view) {
    sf::Text* txt = new sf::Text("hello", *font);
    txt->setString("hello");
    txt->setPosition(50,50);
    txt->setCharacterSize(30);
    txt->setStyle(sf::Text::Bold);
    txt->setColor(sf::Color::Magenta);
    view->addDrawable(txt);
}
