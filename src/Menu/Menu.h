#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>

#include "../Game/GameView.h"

class Menu {
public:
    Menu();
    virtual ~Menu();

    void loadGame();
    void draw(GameView* view);

    void incIndex();
    void decIndex();

private:
    sf::Font* font;
    sf::Texture texture;
    sf::Sprite selector;

    unsigned int index;
    std::vector<sf::Text*> options;
};

#endif // MENU_H
