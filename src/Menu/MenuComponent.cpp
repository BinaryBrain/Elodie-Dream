#include "MenuComponent.h"

MenuComponent::MenuComponent() {
    font = new sf::Font();
    font->loadFromFile("assets/fonts/arial.ttf");
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
