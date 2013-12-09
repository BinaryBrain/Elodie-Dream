#include "Menu.h"

Menu::Menu(std::string label): MenuComponent(label) {

    texture.loadFromFile("assets/img/sprites/menu/selector.png");
    selector.setTexture(texture);

    isMenu = true;
}

Menu::~Menu() {
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

    view->addDrawable(ViewLayer::MENU, &background);

    for(unsigned int i(0); i < items.size(); ++i) {
        items[i]->getText()->setPosition(posX, posY+50*i);
        if(items[i]->isASaveItem()) {
            SaveItem* save = dynamic_cast<SaveItem*>(items[i]);
            std::string date = save->getDate();
            sf::Text* t = save->getText();
            t->setString(date);
            view->addDrawable(ViewLayer::MENU, t);
        }
        else if(items[i]->isALoadItem()) {
            LoadItem* save = dynamic_cast<LoadItem*>(items[i]);
            std::string date = save->getDate();
            sf::Text* t = save->getText();
            t->setString(date);
            view->addDrawable(ViewLayer::MENU, t);
        }
        else {
            view->addDrawable(ViewLayer::MENU, (items[i]->getText()));
        }
    }

    background.setSize(sf::Vector2f(300,50*(items.size())));
    background.setOutlineColor(sf::Color::Blue);
    background.setFillColor((sf::Color(0x00, 0x00, 0x00, 0x7f)));
    background.setOutlineThickness(3);
    background.setPosition(posX-60, posY-5);

    selector.setPosition(150, 5+100+50*index);
    selector.setScale(0.25, 0.25);
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

MenuComponent* Menu::getSelectedItem() {
    return items[index];
}

std::pair<GameState, std::string> Menu::execute() {
    std::string item = items[index]->getText()->getString();
    return items[index]->execute();
}
