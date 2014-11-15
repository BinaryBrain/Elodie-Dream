#ifndef COLLIDE_H_INCLUDED
#define COLLIDE_H_INCLUDED

#include "../Sprite/TileSprite.h"

class Collide
{
public:
    std::map< std::string, float > top = {{"surface", 0}, {"distance", 0}};
    std::map< std::string, float > right = {{"surface", 0}, {"distance", 0}};
    std::map< std::string, float > bottom = {{"surface", 0}, {"distance", 0}};
    std::map< std::string, float > left = {{"surface", 0}, {"distance", 0}};
    TileType ground;
};

#endif // COLLIDE_H_INCLUDED
