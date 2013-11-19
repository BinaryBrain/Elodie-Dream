#include "Menu.h"
#include <SFML/Graphics.hpp>

Menu::Menu() {
    font = new sf::Font();
    font->loadFromFile("assets/fonts/arial.ttf");
}

Menu::~Menu() {

}

void Menu::draw(GameView* view) {
    std::vector<sf::Text*> options;
    options.push_back(new sf::Text("New Game", *font));
    options.push_back(new sf::Text("Load", *font));
    options.push_back(new sf::Text("Settings", *font));
    options.push_back(new sf::Text("Quit", *font));

    for(unsigned int i(0); i < options.size(); ++i) {
        options[i]->setPosition(100,100+50*i);
        options[i]->setCharacterSize(30);
        options[i]->setStyle(sf::Text::Bold);
        options[i]->setColor(sf::Color::Magenta);
        view->addDrawable(options[i]);
    }
}
