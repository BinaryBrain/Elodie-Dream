#ifndef MENUITEM_H
#define MENUITEM_H

#include "MenuComponent.h"

class MenuItem : public MenuComponent {
public:
    MenuItem(std::string label, GameState state);
    virtual ~MenuItem();
private:
};

#endif // MENUITEM_H
