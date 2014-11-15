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
#include "../Entity/Portal.h"

class Elodie;

class Mapper
{
public:
    Mapper();
    static void parse(std::string str, TileMap& tiles, EntityMap& entities, Elodie& elodie);
    static void beautify(TileMap& tiles);
    static void print(TileMap& tiles);
    static std::string getFreshID(std::string key);

private:
    static std::map< std::string, int > freshIds;
};

#endif // MAPPARSER_H
