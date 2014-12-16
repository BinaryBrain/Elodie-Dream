#ifndef TILESPRITE_H
#define TILESPRITE_H

#include <iostream>

#include "EnvSprite.h"

enum class TileType
{
    VOID = 0, GROUND, DIRT, ROCK, ICE, BOX, METAL, ASTEROID
};

enum class TileSide
{
    TOP = 0x01,
    BOTTOM = 0X02,
    LEFT = 0X04,
    RIGHT = 0X08,
    TOP_LEFT = 0X10,
    TOP_RIGHT = 0X20,
    BOTTOM_LEFT = 0X40,
    BOTTOM_RIGHT = 0X80,
};

class TileSprite : public EnvSprite
{
public:
    TileSprite(TileType type);
    virtual ~TileSprite();

    TileType getType();
    int getSide();
    void addSide(TileSide side);
    void setSide(TileSide side);

protected:
private:
    TileType type;
    int side;
    sf::Texture texture;

    void setSide(int side);
    void filterSides();
};

#endif // TILESPRITE_H
