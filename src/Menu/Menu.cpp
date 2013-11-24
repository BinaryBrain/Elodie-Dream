#include "Menu.h"

Menu::Menu(std::string label): MenuComponent(label) {

    texture.loadFromFile("assets/img/sprites/menu/selector.png");
    selector.setTexture(texture);

    index = 0;
}

Menu::~Menu() {
    //dtor
}

void Menu::addItem(MenuComponent* item) {
    sf::Text* text = item->getText();

    text->setCharacterSize(30);
    text->setStyle(sf::Text::Bold);
    text->setColor(sf::Color::Magenta);
    item->setText(text);
    items.push_back(item);
}

// Draws the everything in the menu
void Menu::draw(GameView* view) {
    float posX(200);
    float posY(100);

    for(unsigned int i(0); i < items.size(); ++i) {
        items[i]->getText()->setPosition(posX, posY+50*i);
        view->addDrawable((items[i]->getText()));
    }

    selector.setPosition(150, 5+100+50*index);
    selector.setScale(0.25, 0.25);
    view->addDrawable(&selector);
}

void Menu::incIndex() {
    if (index == items.size()-1) index = 0;
    else ++index;
}

void Menu::decIndex() {
    if (index == 0) index = items.size()-1;
    else --index;
}

int Menu::getIndex() {
    return index;
}

std::string Menu::getItemKey() {
    return items[index]->getText()->getString();
}

GameState Menu::execute() {
    std::string option = getItemKey();
    std::cout << "Title key : " << option << std::endl;
    return items[index]->execute();
}
