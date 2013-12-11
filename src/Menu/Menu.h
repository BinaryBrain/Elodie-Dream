#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>

#include "../env.h"
#include "../const.h"
#include "../Game/GameView.h"
#include "MenuComponent.h"
#include "MenuItem.h"
#include "SaveItem.h"
#include "LoadItem.h"

class Menu : public MenuComponent {

public:
    Menu(std::string label);
    virtual ~Menu();

    void addItem(MenuComponent* item, bool isParent = false);
    void draw(GameView* view);
    void incIndex();
    void decIndex();
    int getIndex();
    void showBackground();
    void hideBackground();

    MenuComponent* getSelectedItem();

    std::pair<GameState, MenuComponent*> execute();

private:
    sf::Texture selectortexture;
    sf::Sprite selector;

    sf::Texture tbgTexture;
    sf::Sprite tbg;

    sf::RectangleShape background;

    std::vector<MenuComponent*> items;

    std::vector<bool> isParent;

    unsigned int index = 0;

    bool withBackground = true;
};

#endif // MENU_H
