#ifndef MENUCOMPONENT_H
#define MENUCOMPONENT_H

#include <SFML/Graphics.hpp>
#include "../env.h"
#include "../font.h"

class MenuComponent {
public:
    MenuComponent(std::string label, GameState state);
    virtual ~MenuComponent();

    sf::Text* getText();
    void setText(sf::Text* text);

    std::string getLabel();
    void setLabel(std::string label);

    GameState getState();
    void setState(GameState state);

    bool isAMenu();

protected:
    std::vector<MenuComponent*> items;
    sf::Text* text;
    std::string label;
    GameState state;

    bool isMenu = false;
};

#endif // MENUCOMPONENT_H
