#ifndef TITLEMENU_H
#define TITLEMENU_H

#include <Menu.h>


class TitleMenu : public Menu
{
public:
    static const std::string STATS_LABEL;
    static const std::string RESUME_LABEL;
    static const std::string LEAVELEVEL_LABEL;

    TitleMenu(const std::string& label, GameState state);
    virtual ~TitleMenu();

    void toLevelMenu();
    void toNormalMenu();
    void toTitleMenu();

private:
};

#endif // TITLEMENU_H
