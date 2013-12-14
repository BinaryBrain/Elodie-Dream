#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>

#include "../env.h"
#include "../const.h"
#include "../Game/GameView.h"
#include "../Utils/Utils.h"
#include "MenuComponent.h"
#include "MenuItem.h"
#include "SaveItem.h"
#include "LoadItem.h"

class Menu : public MenuComponent {

public:
    Menu(std::string label);
    virtual ~Menu();

    void addItem(MenuComponent* item, bool isParent = false);
    void draw(GameView* view, bool inLevel);
    void incIndex(bool inLevel);
    void decIndex(bool inLevel);
    int getIndex();
    void showBackground();
    void hideBackground();

    MenuComponent* getSelectedItem();

    std::pair<GameState, MenuComponent*> execute();
    bool hasBackground();

private:
    sf::Texture selectortexture;
    sf::Sprite selector;

    sf::Texture tbgTexture;
    sf::Sprite tbg;

    sf::RectangleShape background;

    sf::Texture titleTextTexture;
    sf::Sprite titleText;

    std::vector<MenuComponent*> items;

    std::vector<bool> isParent;

    std::map< int, sf::Texture* > poroTextures;
    int poroIndex;

    unsigned int index = 0;

    bool withBackground = true;
};

#endif // MENU_H
