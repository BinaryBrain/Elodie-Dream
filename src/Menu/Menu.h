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

    MenuComponent* getSelectedItem();

    std::pair<GameState, std::string> execute();

private:
    sf::Texture texture;
    sf::Sprite selector;

    sf::RectangleShape background;

    std::vector<MenuComponent*> items;

    unsigned int index = 0;
};

#endif // MENU_H
