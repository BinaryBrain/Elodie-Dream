#ifndef MAPPARSER_H
#define MAPPARSER_H

#include <string>
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "../env.h"

#include "../Sprite/ElodieSprite.h"
#include "../Sprite/EnvSprite.h"
#include "../Sprite/TileSprite.h"
#include "../Entities/Entities.h"
#include "../Entities/Elodie.h"

class Mapper {
    private:
        // ASCII Map
        // Terrain
        static const char MAP_GROUND = '#';

        // Characters
        static const char MAP_ELODIE = 'E';

        // Misc
        static const char MAP_LINE_BREAK = '\n';
        static const char MAP_NULL = ' ';

    public:
        Mapper();
        static void parse(std::string str, TileMap& tiles, EntitieVector& entities);
        static void beautify(TileMap& tiles);
        static void print(TileMap& tiles, EntitieVector& entities);
};

#endif // MAPPARSER_H
