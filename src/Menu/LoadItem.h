#ifndef LOADITEM_H
#define LOADITEM_H

#include "../env.h"
#include "MenuItem.h"
#include "MenuComponent.h"

class LoadItem: public MenuItem {
public:
    LoadItem(std::string label);
    virtual ~LoadItem();

    std::pair<GameState, MenuComponent*> execute();

private:
    std::string date;
};

#endif // LOADITEM_H
