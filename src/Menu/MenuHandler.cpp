#include "MenuHandler.h"

MenuHandler::MenuHandler(GameView* gameView) : Displayable(gameView) {
    MenuComponent* newGame = new MenuComponent("New game", GameState::NEWGAME);
    MenuComponent* quit = new MenuComponent("Quit game", GameState::EXIT);

    MenuComponent* resume = new MenuComponent("Resume", GameState::INLEVEL);
    MenuComponent* backToOv = new MenuComponent("Leave level", GameState::INOVERWORLD);

    std::vector<std::string> lastDiscoveredLevels = {"Level 0","Level 0","Level 0"};
    std::vector<std::string> labels = {"Slot 1", "Slot 2", "Slot 3"};

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

    title->addItem(newGame);
    title->addItem(saveGame);
    title->addItem(loadGame);

    title->addItem(resume);
    title->addItem(backToOv);

    title->addItem(quit);

    SaveHandler* sh = SaveHandler::getInstance();

    for (std::size_t i = 0; i<labels.size(); ++i) {
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
            if(LDL == 0) {
                lastDiscoveredLevels[i] = "Tutorial";
            } else {
                lastDiscoveredLevels[i] = "Level "+ Utils::itos(LDL);
            }
        }

        accessor.close();

        MenuComponent* save = new MenuComponent(labels[i], GameState::SAVE);
        sf::Text* t = save->getText();
        t->setString(lastDiscoveredLevels[i]);
        saveGame->addItem(save);

        MenuComponent* load = new MenuComponent(labels[i], GameState::LOAD);
        load->setText(t);
        loadGame->addItem(load);

        // remove the temporary json
        if(remove(tempJsonFilePath.c_str()) != 0 ) {
            std::cerr << "Error deleting temporary json" << std::endl;
        }
    }

    saveGame->addItem(title, true);
    loadGame->addItem(title, true);


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
