#include "Menu.h"
#include <SFML/Graphics.hpp>

Menu::Menu() {
    opened = false;
}

Menu::~Menu() {

}

void Menu::open() {
    if(!opened) {
        opened = true;
    }
}

void Menu::close() {
    if(opened) {
        opened = false;
    }
}

// Only temporary
void Menu::changeState() {
    opened = !opened;
}

void Menu::draw(GameView* view) {
    sf::Text txt;
    txt.setString("hello");
    txt.setPosition(50,50);
    view->addDrawable(&txt);
}

bool Menu::isOpened() {
    return opened;
}
