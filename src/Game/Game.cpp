#include "Game.h"

Game::Game() {
    this->window = new sf::RenderWindow(sf::VideoMode(1280, 720), "Elodie's Dream: Quest for Poros", sf::Style::Default);
}

Game::~Game() {
    delete this->window;
}

void Game::init() {
    // ???
}

void Game::draw() {

}

Level Game::loadLevel(std::string filename) {
    std::string level = FileHandler::getContent(filename);

    TileMap tiles;
    EntitieVector entities;

    MapParser::parse(level, tiles, entities);
}
