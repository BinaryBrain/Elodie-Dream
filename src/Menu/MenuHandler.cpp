#include "MenuHandler.h"

MenuHandler::MenuHandler(GameView* gameView) : Displayable(gameView) {
    NewGameItem* newGame = new NewGameItem("New game");
    QuitItem* quit = new QuitItem("Quit");
    EnglishItem* english = new EnglishItem("English");

    SaveItem* save1 = new SaveItem("Slot 1", "The date ...");
    SaveItem* save2 = new SaveItem("Slot 2", "The date !");
    SaveItem* save3 = new SaveItem("Slot 3", "Fnu la date !");

    LoadItem* load1 = new LoadItem("Slot 1", "The date ...");
    LoadItem* load2 = new LoadItem("Slot 2", "The date !");
    LoadItem* load3 = new LoadItem("Slot 3", "Fnu la date !");

    title = new Menu("Title menu");
    saveGame = new Menu("Save game");
    loadGame = new Menu("Load game");
    settings = new Menu("Settings");
    language = new Menu("Language");

    title->addItem(newGame);
    title->addItem(saveGame);
    title->addItem(loadGame);
    title->addItem(settings);
    title->addItem(quit);

    saveGame->addItem(save1);
    saveGame->addItem(save2);
    saveGame->addItem(save3);
    saveGame->addItem(title, true);

    loadGame->addItem(load1);
    loadGame->addItem(load2);
    loadGame->addItem(load3);
    loadGame->addItem(title, true);

    settings->addItem(language);
    settings->addItem(title, true);

    language->addItem(english);
    language->addItem(settings, true);

    selectedMenu = title;
}

MenuHandler::~MenuHandler() {
    delete title;

    title = NULL;
    saveGame = NULL;
    loadGame = NULL;
    settings = NULL;
    language = NULL;
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

std::pair<GameState, std::string> MenuHandler::execute() {

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
        } else if (label == "Settings") {
            selectedMenu = settings;
        } else if (label == "Language") {
            selectedMenu = language;
        }

        std::pair<GameState, std::string> p = std::make_pair(GameState::INMENU, label);
        return p;
    }

    std::pair<GameState, std::string> p = std::make_pair(GameState::INMENU, "None");
    return p;
}

void MenuHandler::setNextState(GameState state) {
    this->nextState = state;
}

GameState MenuHandler::getNextState() {
    return this->nextState;
}
