#ifndef MENUCOMPONENT_H
#define MENUCOMPONENT_H

#include <SFML/Graphics.hpp>
#include "../env.h"
#include "../font.h"

class MenuComponent
{
public:
    MenuComponent(const std::string& label, GameState state);
    virtual ~MenuComponent();

    sf::Text* getText();
    void setText(sf::Text* text);

    const std::string& getLabel();
    void setLabel(const std::string& label);

    GameState getState();
    void setState(GameState state);

    bool isAMenu();

    void setVisibility(bool visible);
    bool isVisible();

protected:
    std::vector<MenuComponent*> items;
    sf::Text* text;
    std::string label;
    GameState state;

    bool isMenu = false;
    bool visible = true;
};

#endif // MENUCOMPONENT_H
