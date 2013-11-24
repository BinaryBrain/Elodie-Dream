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
}

MenuHandler::~MenuHandler() {
    //dtor
}

void MenuHandler::display(GameView* view) {
    switch(state) {
        case MenuState::TITLE:
            title->draw(view);
            break;

        case MenuState::SAVES:
            loadGame->draw(view);
            break;

        case MenuState::SETTINGS:
            settings->draw(view);
            break;

        case MenuState::LANGUAGES:
            language->draw(view);
            break;

        default:
            break;
    }

}

void MenuHandler::incIndex() {
    switch(state) {
        case MenuState::TITLE:
            title->incIndex();
            break;

        case MenuState::SAVES:
            loadGame->incIndex();
            break;

        case MenuState::SETTINGS:
            settings->incIndex();
            break;

        case MenuState::LANGUAGES:
            language->incIndex();
            break;

        default:
            break;
    }
}

void MenuHandler::decIndex() {
    switch(state) {
        case MenuState::TITLE:
            title->decIndex();
            break;

        case MenuState::SAVES:
            loadGame->decIndex();
            break;

        case MenuState::SETTINGS:
            settings->decIndex();
            break;

        case MenuState::LANGUAGES:
            language->decIndex();
            break;

        default:
            break;
    }
}

GameState MenuHandler::execute() {
    switch(state) {
        case MenuState::TITLE:
            if (title->getIndex() == 1) state = MenuState::SAVES;
            else if (title->getIndex() == 2) state = MenuState::SETTINGS;
            else return title->execute();
            break;

        case MenuState::SAVES:
            if (loadGame->getIndex() == 3) state = MenuState::TITLE;
            else return loadGame->execute();
            break;

        case MenuState::SETTINGS:
            if (settings->getIndex() == 0) state = MenuState::LANGUAGES;
            else if (settings->getIndex() == 1) state = MenuState::TITLE;
            else return settings->execute();
            break;

        case MenuState::LANGUAGES:
            if (language->getIndex() == 1) state = MenuState::SETTINGS;
            else return language->execute();
            break;

        default:
            break;
    }

    return GameState::INMENU;
}
