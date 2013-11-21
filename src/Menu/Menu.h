#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>

#include "../Game/GameView.h"
#include "../env.h"

class Menu {
public:
    Menu();
    virtual ~Menu();

    void setTitles(std::vector<std::string>const& titles);
    void draw(GameView* view);

    void incIndex();
    void decIndex();
    int getIndex();

private:
    sf::Font* font;
    sf::Texture texture;
    sf::Sprite selector;

    unsigned int index;
    std::vector<sf::Text*> titles;
};

#endif // MENU_H
