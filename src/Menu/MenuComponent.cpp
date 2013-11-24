#include "MenuComponent.h"

MenuComponent::MenuComponent(std::string label) {
    font = new sf::Font();
    font->loadFromFile("assets/fonts/arial.ttf");

    this->text = new sf::Text(label, *font);
}

MenuComponent::~MenuComponent() {
    //dtor
}

sf::Text* MenuComponent::getText() {
    return text;
}

void MenuComponent::setText(sf::Text* text) {
    this->text = text;
}
