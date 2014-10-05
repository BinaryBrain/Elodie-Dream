#include "MenuComponent.h"

MenuComponent::MenuComponent(std::string label, GameState state) {
    this->text = new sf::Text(label, globalFont);
    this->label = label;
    this->state = state;
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

GameState MenuComponent::getState() {
    return state;
}

void MenuComponent::setState(GameState state) {
    this->state = state;
}

bool MenuComponent::isAMenu() {
    return isMenu;
}
