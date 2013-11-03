#ifndef TILESPRITE_H
#define TILESPRITE_H

#include "EnvSprite.h"

enum class TileType { GROUND, GRASS, STONE };

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
