#ifndef MENUITEM_H
#define MENUITEM_H

#include "MenuComponent.h"

class MenuItem : public MenuComponent {
public:
    MenuItem(std::string label);
    virtual ~MenuItem();
private:
};

#endif // MENUITEM_H
