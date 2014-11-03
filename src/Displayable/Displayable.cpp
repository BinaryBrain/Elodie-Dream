#include "Displayable.h"


Displayable::Displayable(GameView* gameView) {
    this->view = new sf::View();
    this->gameView = gameView;
}

Displayable::~Displayable() {
    if (view) {
        delete view;
    }
}

sf::View* Displayable::getView() {
    return this->view;
}
