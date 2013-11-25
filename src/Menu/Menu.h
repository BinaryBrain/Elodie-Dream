#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>

#include "../env.h"
#include "../Game/GameView.h"
#include "MenuComponent.h"
#include "MenuItem.h"

class Menu : public MenuComponent {

public:
    Menu(std::string label);
    virtual ~Menu();

    void addItem(MenuComponent* item);

    void draw(GameView* view);

    void incIndex();
    void decIndex();
    int getIndex();

    std::string getItemKey();
    MenuComponent* getSelectedItem();

    GameState execute();

private:
    sf::Texture texture;
    sf::Sprite selector;

    std::vector<MenuComponent*> items;

    unsigned int index;
};

#endif // MENU_H
