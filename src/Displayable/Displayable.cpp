#include "Displayable.h"

Displayable::Displayable(GameView& g) : gameView(g)
{
}

Displayable::~Displayable()
{
}

sf::View& Displayable::getView()
{
    return (this->view);
}
