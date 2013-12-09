#ifndef MENUCOMPONENT_H
#define MENUCOMPONENT_H

#include <SFML/Graphics.hpp>
#include "../env.h"

class MenuComponent {
public:
    MenuComponent(std::string label);
    virtual ~MenuComponent();

    sf::Text* getText();
    void setText(sf::Text* text);

    virtual std::pair<GameState, std::string> execute() = 0;
    bool isAMenu();
    bool isASaveItem();
    bool isALoadItem();

protected:
    std::vector<MenuComponent*> items;
    sf::Font* font;
    sf::Text* text;
    bool isMenu = false;
    bool isSaveItem = false;
    bool isLoadItem = false;
};

#endif // MENUCOMPONENT_H
