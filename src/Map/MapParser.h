#ifndef MAPPARSER_H
#define MAPPARSER_H

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

#include "../Sprite/ElodieSprite.h"
#include "../Sprite/EnvSprite.h"
#include "../Sprite/TileSprite.h"

class MapParser {
    private:
        // ASCII Map
        // Terrain
        static const char MAP_GROUND = '#';

        // Characters
        static const char MAP_ELODIE = 'E';

        // Misc
        static const char MAP_LINE_BREAK = '\n';

    public:
        MapParser();
        void parse(std::string str, std::vector< std::vector<sf::Sprite*> >& level);
};


#endif // MAPPARSER_H
