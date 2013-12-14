#ifndef BACKOVERWORLDITEM_H
#define BACKOVERWORLDITEM_H

#include "../env.h"
#include "MenuItem.h"

class BackOverWorldItem: public MenuItem {
public:
    BackOverWorldItem(std::string label);
    virtual ~BackOverWorldItem();

    std::pair<GameState, MenuComponent*> execute();

private:
};

#endif // BACKOVERWORLDITEM_H
