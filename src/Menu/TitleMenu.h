#ifndef TITLEMENU_H
#define TITLEMENU_H

#include <Menu.h>


class TitleMenu : public Menu {
public:
    TitleMenu(std::string label, GameState state);
    virtual ~TitleMenu();

    void toLevelMenu();
    void toNormalMenu();
    void toTitleMenu();

private:
};

#endif // TITLEMENU_H
