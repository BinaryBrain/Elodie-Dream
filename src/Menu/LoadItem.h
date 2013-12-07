#ifndef LOADITEM_H
#define LOADITEM_H

#include "../env.h"
#include "MenuItem.h"

class LoadItem: public MenuItem {
public:
    LoadItem(std::string label);
    virtual ~LoadItem();

    std::pair<GameState, std::string> execute();

private:
};

#endif // LOADITEM_H
