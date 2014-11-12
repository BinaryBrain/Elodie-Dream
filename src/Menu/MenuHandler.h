#ifndef MENUHANDLER_H
#define MENUHANDLER_H

#include <SFML/Graphics.hpp>
#include "../env.h"
#include "../Game/GameView.h"
#include "MenuComponent.h"
#include "Menu.h"
#include "TitleMenu.h"
#include "../Displayable/Displayable.h"
#include "../FileHandler/SaveHandler.h"
#include "../Json/JsonAccessor.h"


class MenuHandler : public Displayable {
public:
    static const int CHAR_SIZE;

    MenuHandler(GameView& gameView);
    virtual ~MenuHandler();

    void display();
    void incIndex();
    void decIndex();
    MenuComponent* getCurrentMenuComponent();
    void addCompToMenu(MenuComponent* comp, Menu* menu, bool isParent = false);
    MenuComponent* getMenuComponentFromKey(std::string key);

    void setNextState(GameState state);
    GameState getNextState();
    TitleMenu* getTitleMenu();
    void resetMenu();

    void setInLevel(bool inLevel);

private:
    TitleMenu* title;
    Menu* saveGame;
    Menu* loadGame;

    Menu* selectedMenu;

    sf::Text loading;
    sf::Sprite tbg;

    bool inLevel;

    std::map<std::string, MenuComponent*> compPointers;

    GameState nextState = GameState::INOVERWORLD;
};

#endif // MENUHANDLER_H
