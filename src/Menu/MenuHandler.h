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
#include "../Displayable/Displayable.h"


class MenuHandler : public Displayable{
public:
    MenuHandler();
    virtual ~MenuHandler();

    void display(GameView* view);
    void incIndex();
    void decIndex();
    std::pair<GameState, std::string> execute();

    void setNextState(GameState state);
    GameState getNextState();

private:
    Menu* title;
    Menu* loadGame;
    Menu* settings;
    Menu* language;

    Menu* selectedMenu;

    GameState nextState = GameState::INOVERWORLD;
};

#endif // MENUHANDLER_H
