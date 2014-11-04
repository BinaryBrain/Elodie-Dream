#include "MenuHandler.h"

MenuHandler::MenuHandler(GameView* gameView) : Displayable(gameView) {
    MenuComponent* newGame = new MenuComponent(MENU_NEWGAME_LABEL, GameState::NEWGAME);
    MenuComponent* stats = new MenuComponent(MENU_STATS_LABEL, GameState::INSTATS);
    MenuComponent* resume = new MenuComponent(MENU_RESUME_LABEL, GameState::INLEVEL);
    MenuComponent* backToOv = new MenuComponent(MENU_LEAVELEVEL_LABEL, GameState::INOVERWORLD);
    MenuComponent* quit = new MenuComponent(MENU_QUITGAME_LABEL, GameState::EXIT);

    std::vector<std::string> lastDiscoveredLevels;
    std::vector<std::string> labels;

    for (int i = 1; i <= NUMSLOTS; ++i) {
        lastDiscoveredLevels.push_back("Level 0"); // to know if not initialized later
        labels.push_back(MENU_SLOT_PREFIX_LABEL + Utils::itos(i));
    }

    loading.setFont(globalFont);
    loading.setCharacterSize(SCORES_CHAR_SIZE);
    loading.setString("Loading...");
    loading.setPosition(MENU_LOADING_X, MENU_LOADING_Y);

    sf::Texture* poroTexture = new sf::Texture();
    if(!poroTexture->loadFromFile(MENU_ANIMATED_BACKGROUND_PATH+"/"+Utils::toStringWithLength(MENU_BACKGROUND_FIRST_FRAME, 4)+".png"))
        std::cerr << "Unable to load menu background";

    tbg.setTexture(*poroTexture);

    gameView->getWindow()->draw(tbg);
    gameView->getWindow()->draw(loading);
    gameView->getWindow()->display();

    title = new TitleMenu(MENU_TITLEMENU_LABEL, GameState::INMENU);
    saveGame = new Menu(MENU_SAVEGAME_LABEL, GameState::INMENU);
    loadGame = new Menu(MENU_LOADGAME_LABEL, GameState::INMENU);

    addCompToMenu(newGame, title);
    addCompToMenu(saveGame, title);
    addCompToMenu(loadGame, title);
    addCompToMenu(stats, title);
    addCompToMenu(resume, title);
    addCompToMenu(backToOv, title);
    addCompToMenu(quit, title);

    SaveHandler* sh = SaveHandler::getInstance();

    for (std::size_t i = 0; i < NUMSLOTS; ++i) {
        std::string path = "save/" + labels[i] + ".save";
        sh->setPath(path);
        std::string tempJsonFilePath = "save/temp.json";
        FileHandler::writeContent(tempJsonFilePath, sh->load());

        JsonAccessor accessor;
        bool jsonReady = accessor.load(tempJsonFilePath);

        lastDiscoveredLevels[i] = labels[i];
        std::string key = "lastdiscoveredlevel";

        if(accessor.canTakeElementFrom(key) && jsonReady) {
            int LDL = accessor.getInt(key);
            lastDiscoveredLevels[i] = sh->computeLDLName(LDL);
        }

        accessor.close();

        MenuComponent* save = new MenuComponent(labels[i], GameState::SAVE);
        sf::Text* t = save->getText();
        t->setString(lastDiscoveredLevels[i]);
        addCompToMenu(save, saveGame);

        MenuComponent* load = new MenuComponent(labels[i], GameState::LOAD);
        load->setText(t);
        addCompToMenu(load, loadGame);

        // remove the temporary json
        FileHandler::deleteFile(tempJsonFilePath);
    }

    addCompToMenu(title, saveGame, true);
    addCompToMenu(title, loadGame, true);

    selectedMenu = title;

    saveGame->prepareVisibles();
    loadGame->prepareVisibles();
    title->toTitleMenu();
    gameView->addView(ViewLayer::MENU, this);
}

MenuHandler::~MenuHandler() {
    delete title;

    title = NULL;
    saveGame = NULL;
    loadGame = NULL;
}

void MenuHandler::display() {
    selectedMenu->draw(gameView);
}

void MenuHandler::incIndex() {
    selectedMenu->incIndex();
}

void MenuHandler::decIndex() {
    selectedMenu->decIndex();
}

MenuComponent* MenuHandler::getCurrentMenuComponent() {

    if (!selectedMenu->getSelectedItem()->isAMenu()) {
        return selectedMenu->getSelectedItem();
    } else {
        std::string label = selectedMenu->getSelectedItem()->getText()->getString();
        if (label == MENU_TITLEMENU_LABEL) {
            selectedMenu = title;
        } else if (label == MENU_SAVEGAME_LABEL) {
            selectedMenu = saveGame;
        } else if (label == MENU_LOADGAME_LABEL) {
            selectedMenu = loadGame;
        }

        return selectedMenu;
    }
}

void MenuHandler::addCompToMenu(MenuComponent* comp, Menu* menu, bool isParent) {
    menu->addItem(comp, isParent);
    compPointers.insert(std::pair<std::string, MenuComponent*>(comp->getLabel(), comp));
}

MenuComponent* MenuHandler::getMenuComponentFromKey(std::string key) {
    try {
        return compPointers.at(key);
    }
    catch (const std::out_of_range& oor) {
        std::cerr << "Could not find " << key<< " in compPointers" << std::endl;
        return compPointers[0];
    }
}

void MenuHandler::setNextState(GameState state) {
    this->nextState = state;
}

GameState MenuHandler::getNextState() {
    return this->nextState;
}

TitleMenu* MenuHandler::getTitleMenu() {
    return title;
}

void MenuHandler::resetMenu() {
    selectedMenu = title;
}

void MenuHandler::setInLevel(bool inLevel) {
    this->inLevel = inLevel;
}
