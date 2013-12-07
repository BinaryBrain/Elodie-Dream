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

    virtual GameState execute() = 0;
    bool isAMenu();

protected:
    std::vector<MenuComponent*> items;
    sf::Text* text;
    sf::Font* font;
    bool isMenu = false;
};

#endif // MENUCOMPONENT_H
