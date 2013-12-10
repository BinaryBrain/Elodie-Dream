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
    std::string getLabel();
    void setLabel(std::string label);

    virtual std::pair<GameState, std::string> execute() = 0;
    bool isAMenu();

protected:
    std::vector<MenuComponent*> items;
    sf::Font* font;
    sf::Text* text;
    std::string label;

    bool isMenu = false;
};

#endif // MENUCOMPONENT_H
