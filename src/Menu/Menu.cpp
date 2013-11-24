#include "Menu.h"

Menu::Menu() {

    texture.loadFromFile("assets/img/sprites/menu/selector.png");
    selector.setTexture(texture);

    index = 0;
}

Menu::~Menu() {
    //dtor
}

// Sets the items (vector of sf::Text) for the itemMenu given a vector of strings
void Menu::setItems(std::vector< std::pair<std::string, char> > const items) {

    //in case we want to change the itemMenu at any time
    itemKeys.clear();
    this->items.clear();

    for (unsigned int i(0); i< items.size(); ++i) {

        MenuComponent* item;
        switch (items[i].second) {
            case 'n' :
                item = new Menu;
                break;
            case 'l' :
                item = new MenuItem;
                break;
            default :
                item = new MenuItem;
                break;
        }

        sf::Text* text = new sf::Text(items[i].first, *font);
        item->setText(text);
        this->items.push_back(item);

        /*
        itemKeys.push_back(items[i]);
        sf::Text* item = new sf::Text(items[i], *font);

        item->setPosition(200, 100+50*i);
        item->setCharacterSize(30);
        item->setStyle(sf::Text::Bold);
        item->setColor(sf::Color::Magenta);

        this->items.push_back(item);
        */
    }
}

// Draws the everything on the menu
void Menu::draw(GameView* view) {

    for(unsigned int i(0); i < items.size(); ++i) view->addDrawable((items[i]->getText()));

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
    return itemKeys[index];
}

GameState Menu::getCurrentItem() {
    std::string option = getItemKey();
    std::cout << "Title key : " << option << std::endl;
    if (option == itemKeys[0]) return GameState::INOVERWORLD; // New game
    if (option == itemKeys[3]) return GameState::EXIT; // Quit
    return GameState::INMENU;
}
