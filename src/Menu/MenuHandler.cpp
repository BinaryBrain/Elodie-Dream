#include "MenuHandler.h"

MenuHandler::MenuHandler(GameView* gameView) : Displayable(gameView) {
    NewGameItem* newGame = new NewGameItem("New game");
    QuitItem* quit = new QuitItem("Quit game");

    ResumeItem* resume = new ResumeItem("Resume");
    BackOverWorldItem* backToOv = new BackOverWorldItem("Leave level");

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

    title = new Menu("Title menu");
    saveGame = new Menu("Save game");
    loadGame = new Menu("Load game");

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
        accessor.load(tempJsonFilePath);

        lastDiscoveredLevels[i] = labels[i];
        std::string key = "lastdiscoveredlevel";

        if(accessor.canTakeElementFrom(key)) {
            int LDL = accessor.getInt(key);
            if(LDL == 0) {
                lastDiscoveredLevels[i] = "Tutorial";
            } else {
                lastDiscoveredLevels[i] = "Level "+ Utils::itos(LDL);
            }
        }

        SaveItem* save = new SaveItem(labels[i]);
        sf::Text* t = save->getText();
        t->setString(lastDiscoveredLevels[i]);
        saveGame->addItem(save);

        LoadItem* load = new LoadItem(labels[i]);
        load->setText(t);
        loadGame->addItem(load);

        accessor.close();

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

std::pair<GameState, MenuComponent*> MenuHandler::execute() {

    if (!selectedMenu->getSelectedItem()->isAMenu()) {
        return selectedMenu->execute();
    } else {
        std::string label = selectedMenu->getSelectedItem()->getText()->getString();
        if (label == "Title menu") {
            selectedMenu = title;
        } else if (label == "Save game") {
            selectedMenu = saveGame;
        } else if (label == "Load game") {
            selectedMenu = loadGame;
        }

        std::pair<GameState, MenuComponent*> p = std::make_pair(GameState::INMENU, selectedMenu);
        return p;
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
