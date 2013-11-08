#include "Level.h"

Level::Level() {

}

Level::Level(std::string filename) {
    this->loadLevel(filename);
}

Level::~Level() {
    //dtor
}

void Level::loadLevel(std::string filename) {
    std::string levelSource = FileHandler::getContent(filename);

    Mapper::parse(levelSource, this->tiles, this->entities);
}
