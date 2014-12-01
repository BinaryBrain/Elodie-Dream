#include "Menu.h"

const std::string Menu::SELECTOR_PATH = "assets/img/sprites/poro.png";

Menu::Menu(const std::string& label, GameState state): MenuComponent(label, state)
{
    selectortexture.loadFromFile(SELECTOR_PATH, sf::IntRect(102, 16, 120, 30));
    selector.setTexture(selectortexture);

    background.setOutlineColor(MENU_BACKGROUND_OUTLINE_COLOR);
    background.setFillColor((sf::Color(0x00, 0x00, 0x00, 0x7f)));
    background.setOutlineThickness(3);
    background.setPosition(MENU_X-60, MENU_Y-5);

    isMenu = true;
}

Menu::~Menu()
{
    if(text)
    {
        delete text;
        text = NULL;
    }

    for(size_t i = 0; i < items.size(); ++i)
    {
        if (items[i] && !isParent[i])
        {
            delete items[i];
            items[i] = NULL;
        }
    }
}

void Menu::addItem(MenuComponent* item, bool isParent)
{
    sf::Text* text = item->getText();

    text->setCharacterSize(MENU_CHAR_SIZE);
    text->setStyle(sf::Text::Bold);
    text->setColor(MENU_ITEM_COLOR);
    item->setText(text);
    items.push_back(item);
    this->isParent.push_back(isParent);
}

// Draws the everything in the menu
void Menu::draw(GameView& view)
{
    background.setSize(sf::Vector2f(MENU_WIDTH, MENU_ITEMS_INTERSPACE * visibles.size()));
    view.addDrawable(ViewLayer::MENU, &background);

    for (size_t i = 0; i < visibles.size(); ++i)
    {
        visibles[i]->getText()->setPosition(MENU_X, MENU_Y + MENU_ITEMS_INTERSPACE * i);
        view.addDrawable(ViewLayer::MENU, (visibles[i]->getText()));
    }

    selector.setPosition(MENU_X - 40, MENU_Y + 10 + MENU_ITEMS_INTERSPACE * index);
    view.addDrawable(ViewLayer::MENU, &selector);
}

void Menu::incIndex()
{
    if (index == visibles.size() - 1)
    {
        index = 0;
    }
    else
    {
        ++index;
    }
}

void Menu::decIndex()
{
    if (index == 0)
    {
        index = visibles.size() - 1;
    }
    else
    {
        --index;
    }
}

int Menu::getIndex()
{
    return index;
}

MenuComponent* Menu::getSelectedItem()
{
    return visibles[index];
}

void Menu::prepareVisibles()
{
    visibles.clear();
    for (size_t i = 0; i < items.size(); ++i)
    {
        if (items[i]->isVisible())
        {
            visibles.push_back(items[i]);
        }
    }
}
