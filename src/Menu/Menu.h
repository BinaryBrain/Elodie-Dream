#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>

#include "../env.h"
#include "../Game/GameView.h"
#include "MenuComponent.h"
#include "MenuItem.h"

class Menu : public MenuComponent {

public:
    Menu();
    virtual ~Menu();

    void setItems(std::vector< std::pair<std::string, char> > const items);
    void draw(GameView* view);

    void incIndex();
    void decIndex();
    int getIndex();
    std::string getItemKey();

    GameState getCurrentItem();

private:
    sf::Texture texture;
    sf::Sprite selector;

    unsigned int index;
    std::vector<std::string> itemKeys;
    //std::vector<sf::Text*> items;
};

#endif // MENU_H
