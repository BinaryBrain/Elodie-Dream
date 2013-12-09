#ifndef LOADITEM_H
#define LOADITEM_H

#include "../env.h"
#include "MenuItem.h"

class LoadItem: public MenuItem {
public:
    LoadItem(std::string label, std::string date);
    virtual ~LoadItem();

    std::pair<GameState, std::string> execute();
    std::string getDate();

private:
    std::string date;
};

#endif // LOADITEM_H
