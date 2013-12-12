#include "Mapper.h"
#include "../Entity/Elodie.h"
#include "../Entity/Enemy/Sheep.h"
#include "../Entity/Enemy/MagmaCube.h"
#include "../Entity/Enemy/Spikes.h"

std::map< std::string, int > Mapper::freshIds;

Mapper::Mapper() {
}

// The parser takes the ASCII level and modify the the TileMap and the EntityVector
void Mapper::parse(std::string asciiLevel, TileMap& tiles, EntityMap& entities, Elodie* elodie) {
    unsigned int y = 0;
    unsigned int x = 0;
    bool isEntity = true;
    for(unsigned int i = 0; i < asciiLevel.length(); i++) {
        isEntity = true;
        if(y >= tiles.size()) {
            tiles.push_back(std::vector<TileSprite*>());
        }

        // Entities
        switch(asciiLevel[i]) {
        case MAP_ELODIE:
            elodie->reset();
            elodie->setPosition(x*32 - 21, y*32 - 32);
            entities.insert(std::make_pair("elodie", elodie));
            break;

        case MAP_SHEEP:
            entities.insert(std::make_pair(getFreshID("sheep"), new Sheep(x*32, y*32)));
            break;
        case MAP_MAGMACUBE:
            entities.insert(std::make_pair(getFreshID("magmacube"), new MagmaCube(x*32, y*32)));
            break;
        case MAP_SPIKES:
            entities.insert(std::make_pair(getFreshID("spikes"), new Spikes(x*32, y*32)));
            break;
        case MAP_PORTAL:
            entities.insert(std::make_pair(getFreshID("portal"), new Portal(x*32, y*32)));
            break;
        default:
            isEntity = false;
            break;
        }

        switch(asciiLevel[i]) {
        // Terrain
        case MAP_GROUND:
            tiles[y].push_back(new TileSprite(TileType::ROCK));
            break;

        case MAP_LINE_BREAK:
            y++;
            x=-1;
            break;

        case MAP_NULL:
        case MAP_NULL2:
            tiles[y].push_back(NULL);
            break;

        default:
            tiles[y].push_back(NULL);
            if(!isEntity) {
                std::cout << "[Warning] Mapper: tile type not found: '" << asciiLevel[i] << "'" << std::endl;
            }
            break;
        }

        ++x;
    }
}

// Once the Map is parsed, we can automaticaly choose the right tiles
void Mapper::beautify(TileMap& tiles) {
    for(unsigned int y=0; y<tiles.size(); y++) {
        for(unsigned int x=0; x<tiles[y].size(); x++) {
            if(tiles[y][x]) {
                if((y >= 1 && !tiles[y-1][x]) || y == 0) {
                    tiles[y][x]->addSide(TileSide::TOP);
                }

                if((y < tiles.size()-1 && !tiles[y+1][x]) || y == tiles.size()-1) {
                    tiles[y][x]->addSide(TileSide::BOTTOM);
                }

                if((x >= 1 && !tiles[y][x-1]) || x == 0) {
                    tiles[y][x]->addSide(TileSide::LEFT);
                }

                if((x < tiles[y].size()-1 && !tiles[y][x+1]) || x == tiles[y].size()-1) {
                    tiles[y][x]->addSide(TileSide::RIGHT);
                }

                if((x >= 1 && y >= 1 && !tiles[y-1][x-1]) || (x == 0 && y == 0)) {
                    tiles[y][x]->addSide(TileSide::TOP_LEFT);
                }

                if((x < tiles[y].size()-1 && y >= 1 && !tiles[y-1][x+1]) || (x == tiles[y].size()-1 && y == 0)) {
                    tiles[y][x]->addSide(TileSide::TOP_RIGHT);
                }

                if((x >= 1 && y < tiles.size()-1 && !tiles[y+1][x-1]) || (x == 0 && y == tiles.size()-1)) {
                    tiles[y][x]->addSide(TileSide::BOTTOM_LEFT);
                }

                if((x < tiles[y].size()-1 && y < tiles.size()-1 && !tiles[y+1][x+1]) || (x == tiles[y].size()-1 && y == tiles.size()-1)) {
                    tiles[y][x]->addSide(TileSide::BOTTOM_RIGHT);
                }
            }
        }
    }
}

// Print the map in the console for testing purpose
void Mapper::print(TileMap& tiles, EntityMap& entities) {
    std::cout << "PRINTING MAP" << std::endl;

    std::string out = "";
    for (TileMap::iterator col = tiles.begin(); col != tiles.end(); ++col) {
        for (std::vector<TileSprite*>::iterator it = col->begin(); it != col->end(); ++it) {
            TileSprite* tile = *it;

            if(!tile) {
                out += MAP_NULL;
            } else if(tile->getType() == TileType::GROUND) {
                out += MAP_GROUND;
            }
        }
        out += MAP_LINE_BREAK;
    }

    std::cout << out;
}

std::string Mapper::getFreshID(std::string key) {
    std::stringstream sstm;
    sstm << key << freshIds[key]++;
    return sstm.str();
}

