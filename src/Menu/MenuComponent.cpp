#include "MenuComponent.h"

MenuComponent::MenuComponent(std::string label) {
    font = new sf::Font();
    font->loadFromFile("assets/fonts/arial.ttf");

    this->text = new sf::Text(label, *font);
    this->label = label;
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

std::string MenuComponent::getLabel() {
    return label;
}

void MenuComponent::setLabel(std::string label) {
    this->label = label;
}

bool MenuComponent::isAMenu() {
    return isMenu;
}
