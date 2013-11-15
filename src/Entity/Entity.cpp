#include "Entity.h"

Entity::Entity() {
    sprite = NULL;
}

Entity::~Entity() {
    if(sprite) {
        delete sprite;
    }
}
