#ifndef RESUMEITEM_H
#define RESUMEITEM_H

#include "../env.h"
#include "MenuItem.h"

class ResumeItem: public MenuItem {
public:
    ResumeItem(std::string label);
    virtual ~ResumeItem();

    std::pair<GameState, MenuComponent*> execute();

private:
};

#endif // RESUMEITEM_H
