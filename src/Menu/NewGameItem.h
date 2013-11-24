#ifndef NEWGAMEITEM_H
#define NEWGAMEITEM_H

#include "../env.h"
#include "MenuItem.h"

class NewGameItem : public MenuItem {
public:
    NewGameItem(std::string label);
    virtual ~NewGameItem();
protected:
private:
};

#endif // NEWGAMEITEM_H
