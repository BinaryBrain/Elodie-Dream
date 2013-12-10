#include "MenuHandler.h"

MenuHandler::MenuHandler(GameView* gameView) : Displayable(gameView) {
    NewGameItem* newGame = new NewGameItem("New game");
    QuitItem* quit = new QuitItem("Quit");
    EnglishItem* english = new EnglishItem("English");

    std::vector<std::string> dates = {"","",""};
    std::vector<std::string> labels = {"Slot 1", "Slot 2", "Slot 3"};


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

    JsonAccessor accessor;
    accessor.load("save/dates.json");

    for(unsigned int i(0); i<dates.size(); ++i) {
        dates[i] = labels[i];
        //if(accessor.canTakeElementFrom(labels[i])) dates[i] = accessor.getString(labels[i]);

        SaveItem* save = new SaveItem(labels[i]);
        sf::Text* t = save->getText();
        t->setString(dates[i]);
        saveGame->addItem(save);

        LoadItem* load = new LoadItem(labels[i]);
        t = load->getText();
        t->setString(dates[i]);
        loadGame->addItem(load);
    }

    accessor.close();

    saveGame->addItem(title, true);
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
