#ifndef MAPPARSER_H
#define MAPPARSER_H

#include <string>
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "../env.h"
#include "../const.h"

#include "../Sprite/ElodieSprite.h"
#include "../Sprite/EnvSprite.h"
#include "../Sprite/TileSprite.h"
#include "../Entity/Entity.h"
#include "../Entity/Elodie.h"

class Mapper {
private:

public:
    Mapper();
    static void parse(std::string str, TileMap& tiles, EntityMap& entities, Elodie* elodie);
    static void beautify(TileMap& tiles);
    static void print(TileMap& tiles, EntityMap& entities);
};

#endif // MAPPARSER_H
