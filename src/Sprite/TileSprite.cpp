#include "TileSprite.h"

TileSprite::TileSprite()
{
    type = TileType::GROUND;
}

TileSprite::~TileSprite()
{
    //dtor
}

TileType TileSprite::getType() {
    return this->type;
}
