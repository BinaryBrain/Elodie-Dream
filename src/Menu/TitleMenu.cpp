#include "TitleMenu.h"

const std::string TitleMenu::STATS_LABEL = "Stats";
const std::string TitleMenu::RESUME_LABEL = "Resume";
const std::string TitleMenu::LEAVELEVEL_LABEL = "Leave level";

TitleMenu::TitleMenu(const std::string& label, GameState state): Menu(label, state)
{

}

TitleMenu::~TitleMenu()
{

}

void TitleMenu::toLevelMenu()
{
    index = 0;
    for (size_t i = 0; i < items.size(); ++i)
    {
        std::string itemLabel = items[i]->getLabel();
        if (itemLabel == RESUME_LABEL || itemLabel == LEAVELEVEL_LABEL || itemLabel == STATS_LABEL)
        {
            items[i]->setVisibility(true);
        }
    }
    prepareVisibles();
}

void TitleMenu::toNormalMenu()
{
    index = 0;
    for (size_t i = 0; i < items.size(); ++i)
    {
        std::string itemLabel = items[i]->getLabel();
        if (itemLabel == RESUME_LABEL || itemLabel == LEAVELEVEL_LABEL)
        {
            items[i]->setVisibility(false);
        }
        else if (itemLabel == STATS_LABEL)
        {
            items[i]->setVisibility(true);
        }
    }
    prepareVisibles();
}

void TitleMenu::toTitleMenu()
{
    index = 0;
    for (size_t i = 0; i < items.size(); ++i)
    {
        std::string itemLabel = items[i]->getLabel();
        if (itemLabel == RESUME_LABEL || itemLabel == LEAVELEVEL_LABEL || itemLabel == STATS_LABEL)
        {
            items[i]->setVisibility(false);
        }
    }
    prepareVisibles();
}
