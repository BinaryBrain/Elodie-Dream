#include "GameContent.h"

GameContent::GameContent() {
    //ctor
}

GameContent::~GameContent() {
    delete elodie;
    elodie = NULL;
}

void GameContent::save() {
    // write content to save with the savehandler
}

Elodie* GameContent::getElodie() {
    return elodie;
}

void GameContent::setElodie(Elodie* elodie) {
    this->elodie = elodie;
}
