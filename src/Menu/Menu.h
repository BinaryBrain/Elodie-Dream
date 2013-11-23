#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>

#include "../env.h"
#include "../Game/GameView.h"


class Menu {

public:
    Menu();
    virtual ~Menu();

    void setItems(std::vector<std::string>const& items);
    void draw(GameView* view);

    void incIndex();
    void decIndex();
    int getIndex();
    std::string getItemKey();

    GameState getCurrentItem();

private:
    sf::Font* font;
    sf::Texture texture;
    sf::Sprite selector;

    unsigned int index;
    std::vector<std::string> itemKeys;
    std::vector<sf::Text*> items;
};

#endif // MENU_H
