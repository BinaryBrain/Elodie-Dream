#ifndef SAVEITEM_H
#define SAVEITEM_H

#include "../env.h"
#include "MenuItem.h"
#include "MenuComponent.h"

class SaveItem: public MenuItem {
public:
    SaveItem(std::string label);
    virtual ~SaveItem();

    std::pair<GameState, MenuComponent*> execute();

private:
};

#endif // SAVEITEM_H
