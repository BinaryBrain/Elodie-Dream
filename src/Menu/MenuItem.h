#ifndef MENUITEM_H
#define MENUITEM_H

#include "MenuComponent.h"

class MenuItem : public MenuComponent {
public:
    MenuItem();
    virtual ~MenuItem();

    void setItems(std::vector< std::pair<std::string, char> > const items);

protected:
private:
};

#endif // MENUITEM_H
