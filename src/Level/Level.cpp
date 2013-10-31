#include "Level.h"

Level::Level()
{
    //ctor
}

Level::~Level()
{
    //dtor
}

void Level::loadLevel(std::string filename) {
    std::string level = FileHandler::getContent(filename);
    TileMap tiles = TileMap();
    EntitieMap entities = EntitieMap();

    MapParser::parse(level, tiles, entities);
}
