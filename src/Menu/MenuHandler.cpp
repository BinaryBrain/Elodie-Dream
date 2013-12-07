#include "MenuHandler.h"

MenuHandler::MenuHandler() {
    NewGameItem* newGame = new NewGameItem("New game");
    QuitItem* quit = new QuitItem("Quit");
    EnglishItem* english = new EnglishItem("English");
    SaveItem* save1 = new SaveItem("Slot 1");
    SaveItem* save2 = new SaveItem("Slot 2");
    SaveItem* save3 = new SaveItem("Slot 3");

    title = new Menu("Title menu");
    loadGame = new Menu("Load game");
    settings = new Menu("Settings");
    language = new Menu("Language");

    title->addItem(newGame);
    title->addItem(loadGame);
    title->addItem(settings);
    title->addItem(quit);

    loadGame->addItem(save1);
    loadGame->addItem(save2);
    loadGame->addItem(save3);
    loadGame->addItem(title);

    settings->addItem(language);
    settings->addItem(title);

    language->addItem(english);
    language->addItem(settings);

    selectedMenu = title;
}

MenuHandler::~MenuHandler() {

}

void MenuHandler::display(GameView* view) {
    selectedMenu->draw(view);
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

void MenuHandler::setNextState(GameState state){
    this->nextState = state;
}

GameState MenuHandler::getNextState() {
    return this->nextState;
}
