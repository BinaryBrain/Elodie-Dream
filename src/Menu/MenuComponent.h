#ifndef MENUCOMPONENT_H
#define MENUCOMPONENT_H

#include <SFML/Graphics.hpp>
#include "../env.h"

class MenuComponent {
public:
    MenuComponent(std::string label);
    ~MenuComponent();

    sf::Text* getText();
    void setText(sf::Text* text);

protected:
    std::vector<MenuComponent*> items;
    sf::Font* font;
    sf::Text* text;
};

#endif // MENUCOMPONENT_H
