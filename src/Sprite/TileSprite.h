#ifndef TILESPRITE_H
#define TILESPRITE_H

#include "EnvSprite.h"

enum TileType { TILE_GROUND, TILE_GRASS, TILE_STONE };

class TileSprite : public EnvSprite
{
    public:
        TileSprite();
        virtual ~TileSprite();

        TileType getType();
    protected:
    private:
        TileType type;
};

#endif // TILESPRITE_H
