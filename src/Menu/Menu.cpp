#include "Menu.h"

Menu::Menu(std::string label): MenuComponent(label) {
    selectortexture.loadFromFile(MENU_SELECTOR_PATH, sf::IntRect(102, 16, 120, 30));
    selector.setTexture(selectortexture);

    background.setOutlineColor(MENU_BACKGROUND_OUTLINE_COLOR);
    background.setFillColor((sf::Color(0x00, 0x00, 0x00, 0x7f)));
    background.setOutlineThickness(3);
    background.setPosition(MENU_X-60, MENU_Y-5);

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

    text->setCharacterSize(MENU_CHAR_SIZE);
    text->setStyle(sf::Text::Bold);
    text->setColor(MENU_ITEM_COLOR);
    item->setText(text);
    items.push_back(item);
    this->isParent.push_back(isParent);
}

// Draws the everything in the menu
void Menu::draw(GameView* view, bool inLevel) {

    if (label == "Title menu" && !inLevel) {

        background.setSize(sf::Vector2f(MENU_WIDTH, MENU_ITEMS_INTERSPACE*(items.size()-2)));
        view->addDrawable(ViewLayer::MENU, &background);

        for(unsigned int i(0); i < items.size(); ++i) {
            if(items[i]->getLabel() != "Leave level" && items[i]->getLabel() != "Resume") {
                int tmpi = i > 2 ? i-2 : i;
                items[i]->getText()->setPosition(MENU_X, MENU_Y+MENU_ITEMS_INTERSPACE*tmpi);
                view->addDrawable(ViewLayer::MENU, (items[i]->getText()));
            }
        }
        int tmpIndex = index > 2 ? index-2 : index;
        selector.setPosition(MENU_X-40, MENU_Y+10+MENU_ITEMS_INTERSPACE*tmpIndex);
        view->addDrawable(ViewLayer::MENU, &selector);
    } else {
        background.setSize(sf::Vector2f(MENU_WIDTH, MENU_ITEMS_INTERSPACE*(items.size())));
        view->addDrawable(ViewLayer::MENU, &background);

        for(unsigned int i(0); i < items.size(); ++i) {
            items[i]->getText()->setPosition(MENU_X, MENU_Y+MENU_ITEMS_INTERSPACE*i);
            view->addDrawable(ViewLayer::MENU, (items[i]->getText()));
        }

        selector.setPosition(MENU_X-40, MENU_Y+10+MENU_ITEMS_INTERSPACE*index);
        view->addDrawable(ViewLayer::MENU, &selector);
    }
}

void Menu::incIndex(bool inLevel) {
    if (index == items.size()-1) index = 0;
    else ++index;
    if(!inLevel && label == "Title menu" && (index == 3 || index == 4)) {
        index = 5;
    }
}

void Menu::decIndex(bool inLevel) {
    if (index == 0) index = items.size()-1;
    else --index;
    if(!inLevel && label == "Title menu" && (index == 3 || index == 4)) {
        index = 2;
    }
}

int Menu::getIndex() {
    return index;
}

MenuComponent* Menu::getSelectedItem() {
    return items[index];
}

std::pair<GameState, MenuComponent*> Menu::execute() {
    return items[index]->execute();
}
