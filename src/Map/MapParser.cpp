#include "MapParser.h"

MapParser::MapParser() {

}

void MapParser::parse(std::string str, std::vector< std::vector<sf::Sprite*> >& level) {
    unsigned int x = 0;

    for(unsigned int i = 0; i < str.length(); i++) {
        switch(str[i]) {
            case MAP_ELODIE:
                level[x].push_back(new ElodieSprite());
                break;

            case MAP_GROUND:
                level[x].push_back(new TileSprite()); // Tile::GROUND
                break;

            case MAP_LINE_BREAK:
                x = 0;
                break;

            default:
                // FIXME: Blank Sprite?
                level[x].push_back(NULL);
                break;
        }
    }
}
