#include "MenuHandler.h"

MenuHandler::MenuHandler() {
    NewGameItem* newGame = new NewGameItem("New game");
    QuitItem* quit = new QuitItem("Quit");
    EnglishItem* english = new EnglishItem("English");
    SaveItem* save1 = new SaveItem("Save slot 1");
    SaveItem* save2 = new SaveItem("Save slot 2");
    SaveItem* save3 = new SaveItem("Save slot 3");

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

GameState MenuHandler::execute() {

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

    }

    return GameState::INMENU;
}

void MenuHandler::setNextState(GameState state){
    this->nextState = state;
}

GameState MenuHandler::getNextState() {
    return this->nextState;
}
