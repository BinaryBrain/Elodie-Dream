#include "TileSprite.h"

TileSprite::TileSprite(TileType type)
{
    this->type = type;
}

TileSprite::~TileSprite()
{
    //dtor
}

TileType TileSprite::getType() {
    return this->type;
}
