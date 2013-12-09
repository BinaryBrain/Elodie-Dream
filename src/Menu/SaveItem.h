#ifndef SAVEITEM_H
#define SAVEITEM_H

#include "../env.h"
#include "MenuItem.h"

class SaveItem: public MenuItem {
public:
    SaveItem(std::string label, std::string date);
    virtual ~SaveItem();

    std::pair<GameState, std::string> execute();
    std::string getDate();

private:
    std::string date;
};

#endif // SAVEITEM_H
