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

    selected = title;
}

MenuHandler::~MenuHandler() {
    //dtor
}

void MenuHandler::display(GameView* view) {
    selected->draw(view);
}

void MenuHandler::incIndex() {
    selected->incIndex();
}

void MenuHandler::decIndex() {
    selected->decIndex();
}

GameState MenuHandler::execute() {
    switch(state) {
        case MenuState::TITLE:
            if (title->getIndex() == 1) {
                state = MenuState::SAVES;
                selected = loadGame;
            }
            else if (title->getIndex() == 2) {
                state = MenuState::SETTINGS;
                selected = settings;
            }
            else return title->execute();
            break;

        case MenuState::SAVES:
            if (loadGame->getIndex() == 3) {
                state = MenuState::TITLE;
                selected = title;
            }
            else return loadGame->execute();
            break;

        case MenuState::SETTINGS:
            if (settings->getIndex() == 0) {
                state = MenuState::LANGUAGES;
                selected = language;
            }
            else if (settings->getIndex() == 1) {
                state = MenuState::TITLE;
                selected = title;
            }
            else return settings->execute();
            break;

        case MenuState::LANGUAGES:
            if (language->getIndex() == 1) {
                state = MenuState::SETTINGS;
                selected = settings;
            }
            else return language->execute();
            break;

        default:
            break;
    }

    return GameState::INMENU;
}
