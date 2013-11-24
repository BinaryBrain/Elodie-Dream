#ifndef MENUHANDLER_H
#define MENUHANDLER_H


#include <SFML/Graphics.hpp>

#include "../env.h"
#include "../Game/GameView.h"

#include "MenuComponent.h"
#include "Menu.h"
#include "MenuItem.h"

#include "NewGameItem.h"
#include "QuitItem.h"
#include "EnglishItem.h"
#include "SaveItem.h"


class MenuHandler {
public:
    MenuHandler();
    virtual ~MenuHandler();

    void display(GameView* view);

    void incIndex();
    void decIndex();
    GameState execute();

private:
    MenuState state = MenuState::TITLE;
    Menu* title;
    Menu* loadGame;
    Menu* settings;
    Menu* language;
};

#endif // MENUHANDLER_H
