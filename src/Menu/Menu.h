#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>

#include "../env.h"
#include "../const.h"
#include "../Game/GameView.h"
#include "../Utils/Utils.h"
#include "MenuComponent.h"


class Menu : public MenuComponent {

public:
    Menu(std::string label, GameState state);
    virtual ~Menu();

    void addItem(MenuComponent* item, bool isParent = false);
    void draw(GameView* view, bool inLevel);
    void incIndex(bool inLevel);
    void decIndex(bool inLevel);
    int getIndex();
    MenuComponent* getSelectedItem();

    MenuComponent* getCurrentMenuComponent();

private:
    sf::Texture selectortexture;
    sf::Sprite selector;

    sf::RectangleShape background;

    std::vector<MenuComponent*> items;

    std::vector<bool> isParent;

    unsigned int index = 0;
};

#endif // MENU_H
