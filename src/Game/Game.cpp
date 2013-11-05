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

    TileMap tiles;
    EntitieVector entities;

    MapParser::parse(level, tiles, entities);
}
