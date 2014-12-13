#include <stdexcept>
#include "MenuHandler.h"

const int MenuHandler::CHAR_SIZE = 25;

const std::string MenuHandler::NEWGAME_LABEL = "New game";
const std::string MenuHandler::TITLEMENU_LABEL = "Title menu";
const std::string MenuHandler::SAVEGAME_LABEL = "Save game";
const std::string MenuHandler::LOADGAME_LABEL = "Load game";
const std::string MenuHandler::QUITGAME_LABEL = "Quit game";

MenuHandler::MenuHandler(GameView& gameView) : Displayable(gameView)
{
    MenuComponent* newGame = new MenuComponent(NEWGAME_LABEL, GameState::NEWGAME);
    MenuComponent* stats = new MenuComponent(TitleMenu::STATS_LABEL, GameState::INSTATS);
    MenuComponent* resume = new MenuComponent(TitleMenu::RESUME_LABEL, GameState::INLEVEL);
    MenuComponent* backToOv = new MenuComponent(TitleMenu::LEAVELEVEL_LABEL, GameState::INOVERWORLD);
    MenuComponent* quit = new MenuComponent(QUITGAME_LABEL, GameState::EXIT);

    std::vector<std::string> lastDiscoveredLevels;
    std::vector<std::string> labels;

    for (size_t i = 1; i <= SaveHandler::NUMSLOTS; ++i)
    {
        lastDiscoveredLevels.push_back("Level 0"); // to know if not initialized later
        labels.push_back(SaveHandler::SLOT_PREFIX_LABEL + Utils::itos(i));
    }

    loading.setFont(globalFont);
    loading.setCharacterSize(CHAR_SIZE);
    loading.setString("Loading...");
    loading.setPosition(MENU_LOADING_X, MENU_LOADING_Y);

    sf::Texture* poroTexture = new sf::Texture();
    if (!poroTexture->loadFromFile(TitleScreen::ANIMATED_BACKGROUND_PATH+"/"+Utils::toStringWithLength(MENU_BACKGROUND_FIRST_FRAME, 4)+".png"))
    {
        std::cerr << "Unable to load menu background" << std::endl;;
    }

    tbg.setTexture(*poroTexture);

    gameView.getWindow().draw(tbg);
    gameView.getWindow().draw(loading);
    gameView.getWindow().display();

    title = new TitleMenu(TITLEMENU_LABEL, GameState::INMENU);
    saveGame = new Menu(SAVEGAME_LABEL, GameState::INMENU);
    loadGame = new Menu(LOADGAME_LABEL, GameState::INMENU);

    addCompToMenu(newGame, title);
    addCompToMenu(saveGame, title);
    addCompToMenu(loadGame, title);
    addCompToMenu(stats, title);
    addCompToMenu(resume, title);
    addCompToMenu(backToOv, title);
    addCompToMenu(quit, title);

    SaveHandler& sh = SaveHandler::getInstance();

    for (size_t i = 0; i < SaveHandler::NUMSLOTS; ++i)
    {
        std::string path = "save/" + labels[i] + ".save";

        JsonAccessor accessor;
        accessor.setJson(sh.getDecryptedContentFrom(path));

        if (FileHandler::fileExists(path))
        {
            std::vector<int> LDL = {0,0};
            if (accessor.canTakeElementFrom(SaveHandler::VERSION_KEY))
            {
                LDL = accessor.getIntVector(SaveHandler::LDL_KEY);
            }
            else
            {
                LDL[1] = accessor.getInt(SaveHandler::LDL_KEY);
            }

            lastDiscoveredLevels[i] = sh.computeLevelName(LDL);
        }
        else
        {
            lastDiscoveredLevels[i] = labels[i];
        }

        MenuComponent* save = new MenuComponent(labels[i], GameState::SAVE);
        sf::Text* t = save->getText();
        t->setString(lastDiscoveredLevels[i]);
        addCompToMenu(save, saveGame);

        MenuComponent* load = new MenuComponent(labels[i], GameState::LOAD);
        load->setText(t);
        addCompToMenu(load, loadGame);
    }

    addCompToMenu(title, saveGame, true);
    addCompToMenu(title, loadGame, true);

    selectedMenu = title;

    saveGame->prepareVisibles();
    loadGame->prepareVisibles();
    title->toTitleMenu();
    gameView.addView(ViewLayer::MENU, this);
}

MenuHandler::~MenuHandler()
{
    delete title;

    title = NULL;
    saveGame = NULL;
    loadGame = NULL;
}

void MenuHandler::display()
{
    selectedMenu->draw(gameView);
}

void MenuHandler::incIndex()
{
    selectedMenu->incIndex();
}

void MenuHandler::decIndex()
{
    selectedMenu->decIndex();
}

MenuComponent* MenuHandler::getCurrentMenuComponent()
{

    if (!selectedMenu->getSelectedItem()->isAMenu())
    {
        return selectedMenu->getSelectedItem();
    }
    else
    {
        std::string label = selectedMenu->getSelectedItem()->getText()->getString();
        if (label == TITLEMENU_LABEL)
        {
            selectedMenu = title;
        }
        else if (label == SAVEGAME_LABEL)
        {
            selectedMenu = saveGame;
        }
        else if (label == LOADGAME_LABEL)
        {
            selectedMenu = loadGame;
        }

        return selectedMenu;
    }
}

void MenuHandler::addCompToMenu(MenuComponent* comp, Menu* menu, bool isParent)
{
    menu->addItem(comp, isParent);
    compPointers.insert(std::pair<std::string, MenuComponent*>(comp->getLabel(), comp));
}

MenuComponent* MenuHandler::getMenuComponentFromKey(std::string key)
{
    try
    {
        return compPointers.at(key);
    }
    catch (const std::out_of_range& oor)
    {
        std::cerr << "Could not find " << key<< " in compPointers" << std::endl;
        return compPointers[0];
    }
}

void MenuHandler::setNextState(GameState state)
{
    this->nextState = state;
}

GameState MenuHandler::getNextState()
{
    return this->nextState;
}

TitleMenu* MenuHandler::getTitleMenu()
{
    return title;
}

void MenuHandler::resetMenu()
{
    selectedMenu = title;
}

void MenuHandler::setInLevel(bool inLevel)
{
    this->inLevel = inLevel;
}
