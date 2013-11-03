#include "TileSprite.h"

TileSprite::TileSprite()
{
    type = TILE_GROUND;
}

TileSprite::~TileSprite()
{
    //dtor
}

TileType TileSprite::getType() {
    return this->type;
}
