#include "Menu.h"
#include <SFML/Graphics.hpp>

Menu::Menu() {
    font = new sf::Font();
    font->loadFromFile("assets/fonts/arial.ttf");

    texture.loadFromFile("assets/img/sprites/menu/selector.png");
    selector.setTexture(texture);

    index = 0;
}

Menu::~Menu() {

}

// Sets the titles for the menu given a vector of strings
void Menu::setTitles(std::vector<std::string> const& titles) {

    for (unsigned int i(0); i< titles.size(); ++i) {
        sf::Text* title = new sf::Text(titles[i], *font);
        title->setPosition(200, 100+50*i);
        title->setCharacterSize(30);
        title->setStyle(sf::Text::Bold);
        title->setColor(sf::Color::Magenta);
        this->titles.push_back(title);
    }
}

// Draws the everything on the menu
void Menu::draw(GameView* view) {

    for(unsigned int i(0); i < titles.size(); ++i) view->addDrawable(titles[i]);

    selector.setPosition(150, 5+100+50*index);
    selector.setScale(0.25, 0.25);
    view->addDrawable(&selector);
}

void Menu::incIndex() {
    if (index == titles.size()-1) index = 0;
    else ++index;
}

void Menu::decIndex() {
    if (index == 0) index = titles.size()-1;
    else --index;
}

int Menu::getIndex() {
    return index;
}
