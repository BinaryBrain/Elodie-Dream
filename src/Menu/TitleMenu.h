#ifndef TITLEMENU_H
#define TITLEMENU_H

#include <Menu.h>


class TitleMenu : public Menu {
public:
    TitleMenu(std::string label, GameState state);
    virtual ~TitleMenu();

    void toNormalMenu();
    void toLevelMenu();

private:
};

#endif // TITLEMENU_H
