#include "Menu.h"

Menu::Menu(std::string label): MenuComponent(label) {

    selectortexture.loadFromFile("assets/img/sprites/poro.png", sf::IntRect(102, 16, 120, 30));
    selector.setTexture(selectortexture);

    tbgTexture.loadFromFile("assets/img/sprites/menu/background.png");
    tbg.setTexture(tbgTexture);
    tbg.setPosition(0,0);

    isMenu = true;
}

Menu::~Menu() {
    if(text) {
        delete text;
        text = NULL;
    }

    for(unsigned int i(0); i<items.size(); ++i) {
        if(items[i] && !isParent[i]) {
            delete items[i];
            items[i] = NULL;
        }
    }
}

void Menu::addItem(MenuComponent* item, bool isParent) {
    sf::Text* text = item->getText();

    text->setCharacterSize(30);
    text->setStyle(sf::Text::Bold);
    text->setColor(sf::Color::Magenta);
    item->setText(text);
    items.push_back(item);
    this->isParent.push_back(isParent);
}

// Draws the everything in the menu
void Menu::draw(GameView* view) {
    float posX(200);
    float posY(100);

    if(withBackground) {
        view->addDrawable(ViewLayer::MENU, &tbg);
    }

    background.setSize(sf::Vector2f(300,50*(items.size())));
    background.setOutlineColor(sf::Color::Blue);
    background.setFillColor((sf::Color(0x00, 0x00, 0x00, 0x7f)));
    background.setOutlineThickness(3);
    background.setPosition(posX-60, posY-5);
    view->addDrawable(ViewLayer::MENU, &background);

    for(unsigned int i(0); i < items.size(); ++i) {
        items[i]->getText()->setPosition(posX, posY+50*i);
        view->addDrawable(ViewLayer::MENU, (items[i]->getText()));
    }

    selector.setPosition(160, 110+50*index);
    view->addDrawable(ViewLayer::MENU, &selector);
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

void Menu::showBackground () {
    withBackground = true;
}

void Menu::hideBackground () {
    withBackground = false;
}

MenuComponent* Menu::getSelectedItem() {
    return items[index];
}

std::pair<GameState, MenuComponent*> Menu::execute() {
    return items[index]->execute();
}
