#include "Entity.h"

Entity::Entity()
{
    this->m_sprite = NULL;
}

Entity::~Entity()
{
    if(m_sprite) {
        delete m_sprite;
    }
}
