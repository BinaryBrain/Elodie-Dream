#ifndef SAVEITEM_H
#define SAVEITEM_H

#include "../env.h"
#include "MenuItem.h"

class SaveItem: public MenuItem {
public:
    SaveItem(std::string label);
    virtual ~SaveItem();

    std::pair<GameState, std::string> execute();
private:
};

#endif // SAVEITEM_H
