#include "MenuComponent.h"

MenuComponent::MenuComponent(std::string label) {
    this->text = new sf::Text(label, globalFont);
    this->label = label;
}

MenuComponent::~MenuComponent() {

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
