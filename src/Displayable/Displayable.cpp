#include "Displayable.h"


Displayable::Displayable()
{
    //ctor
}

Displayable::~Displayable()
{
    delete view;
}

sf::View* Displayable::getView(){
    return this->view;
}
