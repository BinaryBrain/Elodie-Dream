#ifndef MENUHANDLER_H
#define MENUHANDLER_H


#include <SFML/Graphics.hpp>

#include "../env.h"
#include "../Game/GameView.h"

#include "MenuComponent.h"
#include "Menu.h"

#include "../Displayable/Displayable.h"
#include "../FileHandler/SaveHandler.h"
#include "../Json/JsonAccessor.h"


class MenuHandler : public Displayable{
public:
    MenuHandler(GameView* view);
    virtual ~MenuHandler();

    void display();
    void incIndex();
    void decIndex();
    MenuComponent* getCurrentMenuComponent();

    void setNextState(GameState state);
    GameState getNextState();
    Menu* getTitleMenu();
    void resetMenu();

    void setInLevel(bool inLevel);

private:
    Menu* title;
    Menu* saveGame;
    Menu* loadGame;

    Menu* selectedMenu;

    sf::Text loading;
    sf::Sprite tbg;

    bool inLevel;

    GameState nextState = GameState::INOVERWORLD;
};

#endif // MENUHANDLER_H
