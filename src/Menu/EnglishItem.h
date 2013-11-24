#ifndef ENGLISHITEM_H
#define ENGLISHITEM_H

#include "../env.h"
#include "MenuItem.h"

class EnglishItem : public MenuItem {
public:
    EnglishItem(std::string label);
    virtual ~EnglishItem();

    GameState execute();
private:
};

#endif // ENGLISHITEM_H
