#ifndef SAVEITEM_H
#define SAVEITEM_H

#include "../env.h"
#include "MenuItem.h"

class SaveItem: public MenuItem {
public:
    SaveItem(std::string label);
    virtual ~SaveItem();

    GameState execute();
private:
};

#endif // SAVEITEM_H
