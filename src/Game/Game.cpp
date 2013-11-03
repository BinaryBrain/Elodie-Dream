#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
    //dtor
}

Level Game::loadLevel(std::string filename) {
    std::string level = FileHandler::getContent(filename);

    std::cout << filename << std::endl;
    std::cout << level << std::endl;

    TileMap tiles;
    EntitieMap entities;

    MapParser::parse(level, tiles, entities);

    MapParser::print(tiles, entities);

}
