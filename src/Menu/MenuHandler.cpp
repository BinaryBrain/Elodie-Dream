#include "MenuHandler.h"

MenuHandler::MenuHandler(GameView* gameView) : Displayable(gameView) {
    MenuComponent* newGame = new MenuComponent("New game", GameState::NEWGAME);
    MenuComponent* quit = new MenuComponent("Quit game", GameState::EXIT);

    MenuComponent* resume = new MenuComponent("Resume", GameState::INLEVEL);
    MenuComponent* backToOv = new MenuComponent("Leave level", GameState::INOVERWORLD);

    std::vector<std::string> lastDiscoveredLevels;
    std::vector<std::string> labels;

    for (int i = 1; i <= NUMSLOTS; ++i) {
        lastDiscoveredLevels.push_back("Level 0"); // to know if not initialized later
        labels.push_back("Slot " + Utils::itos(i));
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

    title = new Menu("Title menu", GameState::INMENU);
    saveGame = new Menu("Save game", GameState::INMENU);
    loadGame = new Menu("Load game", GameState::INMENU);

    addCompToMenu(newGame, title);
    addCompToMenu(saveGame, title);
    addCompToMenu(loadGame, title);
    addCompToMenu(resume, title);
    addCompToMenu(backToOv, title);
    addCompToMenu(quit, title);

    SaveHandler* sh = SaveHandler::getInstance();

    for (std::size_t i = 0; i < NUMSLOTS; ++i) {
        std::string path = "save/" + labels[i] + ".save";
        sh->setPath(path);

        std::string json = sh->load();

        // creates a temporary json file for the JsonAccessor
        std::ofstream tempJsonFile;
        std::string tempJsonFilePath = "save/temp.json";

        tempJsonFile.open(tempJsonFilePath);
        tempJsonFile << json << std::endl;
        tempJsonFile.close();

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
        if (remove(tempJsonFilePath.c_str()) != 0 ) {
            std::cerr << "Error deleting temporary json" << std::endl;
        }
    }

    addCompToMenu(title, saveGame, true);
    addCompToMenu(title, loadGame, true);

    selectedMenu = title;
}

MenuHandler::~MenuHandler() {
    delete title;

    title = NULL;
    saveGame = NULL;
    loadGame = NULL;
}

void MenuHandler::display() {
    selectedMenu->draw(gameView, inLevel);
}

void MenuHandler::incIndex() {
    selectedMenu->incIndex(inLevel);
}

void MenuHandler::decIndex() {
    selectedMenu->decIndex(inLevel);
}

MenuComponent* MenuHandler::getCurrentMenuComponent() {

    if (!selectedMenu->getSelectedItem()->isAMenu()) {
        return selectedMenu->getCurrentMenuComponent();
    } else {
        std::string label = selectedMenu->getSelectedItem()->getText()->getString();
        if (label == "Title menu") {
            selectedMenu = title;
        } else if (label == "Save game") {
            selectedMenu = saveGame;
        } else if (label == "Load game") {
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

Menu* MenuHandler::getTitleMenu() {
    return title;
}

void MenuHandler::resetMenu() {
    selectedMenu = title;
}

void MenuHandler::setInLevel(bool inLevel) {
    this->inLevel = inLevel;
}
