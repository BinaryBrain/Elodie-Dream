#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>

#include "../env.h"
#include "../const.h"
#include "../Game/GameView.h"
#include "../Utils/Utils.h"
#include "MenuComponent.h"

class Menu : public MenuComponent
{

public:
    static const std::string SELECTOR_PATH;

    Menu(const std::string& label, GameState state);
    virtual ~Menu();

    void addItem(MenuComponent* item, bool isParent = false);
    void draw(GameView& view);
    void incIndex();
    void decIndex();
    int getIndex();
    MenuComponent* getSelectedItem();
    MenuComponent* getCurrentMenuComponent();
    /**
    * \brief Essential to prepare what's going to be displayed. Should be used after changes in the items's visibility.
    */
    void prepareVisibles();

protected:
    sf::Texture selectortexture;
    sf::Sprite selector;

    sf::RectangleShape background;

    std::vector<MenuComponent*> items;
    std::vector<MenuComponent*> visibles;

    std::vector<bool> isParent;

    unsigned int index = 0;
};

#endif // MENU_H
