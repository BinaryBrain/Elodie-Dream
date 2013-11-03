#include "MapParser.h"

MapParser::MapParser() {

}

void MapParser::parse(std::string str, TileMap& tiles, EntitieMap& entities) {
    unsigned int x = 0;

    // FIXME Use Insert instead of Push_back
    for(unsigned int i = 0; i < str.length(); i++) {
        // Entities
        switch(str[i]) {
            case MAP_ELODIE:
                entities.push_back(new Elodie());
                break;
            default:
                break;
        }

        // Terrain
        switch(str[i]) {
            case MAP_GROUND:
                tiles[x].push_back(new TileSprite()); // Tile::GROUND

                break;

            case MAP_LINE_BREAK:
                // TODO Blank Sprite?
                tiles[x].push_back(NULL);

                x = 0;
                break;

            default:
                // TODO Blank Sprite?
                tiles[x].push_back(NULL);
                break;
        }
    }
}

void MapParser::print(TileMap& tiles, EntitieMap& entities) {
    for (TileMap::iterator col = tiles.begin(); col != tiles.end(); ++col) {
        for (std::vector<TileSprite*>::iterator it = col->begin(); it != col->end(); ++it) {
            TileSprite* tile = *it;

            if(tile) {
                std::cout << ' ';
            }

            if(tile->getType() == TILE_GROUND) {
                std::cout << '#';
            }
        }
    }
}
