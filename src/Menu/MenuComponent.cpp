#include "MenuComponent.h"

MenuComponent::MenuComponent(std::string label) {
    font = new sf::Font();
    font->loadFromFile("assets/fonts/arial.ttf");

    this->text = new sf::Text(label, *font);
}

MenuComponent::~MenuComponent() {
    if(text) {
        delete text;
    }
    if(font) {
        delete font;
    }
    text = NULL;
    font = NULL;
}

sf::Text* MenuComponent::getText() {
    return text;
}

void MenuComponent::setText(sf::Text* text) {
    this->text = text;
}

bool MenuComponent::isAMenu() {
    return isMenu;
}

bool MenuComponent::isASaveItem() {
    return isSaveItem;
}

bool MenuComponent::isALoadItem() {
    return isLoadItem;
}
