#include "Entity.h"

Entity::Entity()
{
    this->sprite = NULL;
}

Entity::~Entity()
{
    if(sprite) {
        delete sprite;
    }
}
