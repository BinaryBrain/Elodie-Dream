#include "Mapper.h"
#include "../Entity/Elodie.h"
#include "../Entity/Enemy/Sheep.h"
#include "../Entity/Enemy/MagmaCube.h"
#include "../Entity/Enemy/Ghost.h"
#include "../Entity/Enemy/Bristle.h"
#include "../Entity/Enemy/Raven.h"
#include "../Entity/Portal.h"
#include "../Entity/Enemy/Spikes.h"
#include "../Entity/Enemy/Alien.h"
#include "../Entity/Enemy/Laser.h"
#include "../Entity/Enemy/Meteorite.h"
#include "../Entity/Poro.h"
#include "../Entity/Bonus.h"

std::map< std::string, int > Mapper::freshIds;

Mapper::Mapper()
{
}

// The parser takes the ASCII level and modify the the TileMap and the EntityVector
void Mapper::parse(std::string asciiLevel, TileMap& tiles, EntityMap& entities, Elodie& elodie)
{
    unsigned int y = 0;
    unsigned int x = 0;
    bool isEntity = true;
    for(size_t i = 0; i < asciiLevel.length(); i++)
    {
        isEntity = true;
        if(y >= tiles.size())
        {
            tiles.push_back(std::vector<TileSprite*>());
        }

        // Entities
        switch(asciiLevel[i])
        {
        case MAP_ELODIE:
            elodie.reset();
            elodie.setPosition(x*32 - 21, y*32 - 32);
            entities.insert(std::make_pair("elodie", &elodie));
            break;

        case MAP_SHEEP:
            entities.insert(std::make_pair(getFreshID("sheep"), new Sheep(x*32, y*32)));
            break;
        case MAP_MAGMACUBE:
            entities.insert(std::make_pair(getFreshID("magmacube"), new MagmaCube(x*32, y*32)));
            break;
        case MAP_GHOST:
            entities.insert(std::make_pair(getFreshID("ghost"), new Ghost(x*32, y*32)));
            break;
        case MAP_BRISTLE:
            entities.insert(std::make_pair(getFreshID("bristle"), new Bristle(x*32, y*32)));
            break;
        case MAP_SPIKES:
            entities.insert(std::make_pair(getFreshID("spikes"), new Spikes(x*32, y*32)));
            break;
        case MAP_LASER:
            entities.insert(std::make_pair(getFreshID("laser"), new Laser(x*32, y*32)));
            break;
        case MAP_ALIEN:
            entities.insert(std::make_pair(getFreshID("alien"), new Alien(x*32, y*32)));
            break;
        case MAP_METEORITE:
            entities.insert(std::make_pair(getFreshID("meteorite"), new Meteorite(x*32, y*32)));
            break;
        case MAP_RAVEN:
            entities.insert(std::make_pair(getFreshID("raven"), new Raven(x*32, y*32)));
            break;
        case MAP_PORTAL:
            if(entities.find("portal") == entities.end())
            {
                entities.insert(std::make_pair("portal", new Portal(x*32, y*32, ENTITYTYPE_MISC, ENTITYNAME_PORTAL, EntityType::MISC, EntityName::PORTAL)));
            }
            break;
        case MAP_ROCKET:
            if(entities.find("portal") == entities.end())
            {
                entities.insert(std::make_pair("portal", new Portal(x*32, y*32, ENTITYTYPE_MISC, ENTITYNAME_ROCKET, EntityType::MISC, EntityName::ROCKET)));
            }
            break;
        case MAP_PORO:
            entities.insert(std::make_pair(getFreshID("poro"), new Poro(x*32, y*32)));
            break;
        case MAP_BONUS:
            entities.insert(std::make_pair(getFreshID("bonus"), new Bonus(x*32, y*32)));
            break;
        default:
            isEntity = false;
            break;
        }

        switch(asciiLevel[i])
        {
        // Terrain
        case MAP_GROUND:
            tiles[y].push_back(new TileSprite(TileType::ROCK));
            break;

        case MAP_ICE:
            tiles[y].push_back(new TileSprite(TileType::ICE));
            break;

        case MAP_DIRT:
            tiles[y].push_back(new TileSprite(TileType::DIRT));
            break;

        case MAP_BOX:
            tiles[y].push_back(new TileSprite(TileType::BOX));
            break;

        case MAP_METAL:
            tiles[y].push_back(new TileSprite(TileType::METAL));
            break;

        case MAP_ASTEROID:
            tiles[y].push_back(new TileSprite(TileType::ASTEROID));
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
            if(!isEntity)
            {
                std::cerr << "[Warning] Mapper: tile type not found: '" << asciiLevel[i] << "'" << std::endl;
            }
            break;
        }

        ++x;
    }
}

// Once the Map is parsed, we can automaticaly choose the right tiles
void Mapper::beautify(TileMap& tiles)
{
    for (size_t y=0; y <tiles.size(); y++)
    {
        for (size_t x=0; x < tiles[y].size(); x++)
        {
            if (tiles[y][x])
            {
                if ((y >= 1 && !tiles[y-1][x]) || y == 0)
                {
                    tiles[y][x]->addSide(TileSide::TOP);
                }

                if ((y < tiles.size()-1 && !tiles[y+1][x]) || y == tiles.size()-1)
                {
                    tiles[y][x]->addSide(TileSide::BOTTOM);
                }

                if ((x >= 1 && !tiles[y][x-1]) || x == 0)
                {
                    tiles[y][x]->addSide(TileSide::LEFT);
                }

                if ((x < tiles[y].size()-1 && !tiles[y][x+1]) || x == tiles[y].size()-1)
                {
                    tiles[y][x]->addSide(TileSide::RIGHT);
                }

                if ((x >= 1 && y >= 1 && !tiles[y-1][x-1]) || (x == 0 && y == 0))
                {
                    tiles[y][x]->addSide(TileSide::TOP_LEFT);
                }

                if ((x < tiles[y].size()-1 && y >= 1 && !tiles[y-1][x+1]) || (x == tiles[y].size()-1 && y == 0))
                {
                    tiles[y][x]->addSide(TileSide::TOP_RIGHT);
                }

                if ((x >= 1 && y < tiles.size()-1 && !tiles[y+1][x-1]) || (x == 0 && y == tiles.size()-1))
                {
                    tiles[y][x]->addSide(TileSide::BOTTOM_LEFT);
                }

                if ((x < tiles[y].size()-1 && y < tiles.size()-1 && !tiles[y+1][x+1]) || (x == tiles[y].size()-1 && y == tiles.size()-1))
                {
                    tiles[y][x]->addSide(TileSide::BOTTOM_RIGHT);
                }
            }
        }
    }
}

// Print the map in the console for testing purpose
void Mapper::print(TileMap& tiles)
{

    std::string out = "";
    for (TileMap::iterator col = tiles.begin(); col != tiles.end(); ++col)
    {
        for (std::vector<TileSprite*>::iterator it = col->begin(); it != col->end(); ++it)
        {
            TileSprite* tile = *it;

            if(!tile)
            {
                out += MAP_NULL;
            }
            else if(tile->getType() == TileType::GROUND)
            {
                out += MAP_GROUND;
            }
        }
        out += MAP_LINE_BREAK;
    }

}

std::string Mapper::getFreshID(std::string key)
{
    std::stringstream sstm;
    sstm << key << freshIds[key]++;
    return sstm.str();
}

