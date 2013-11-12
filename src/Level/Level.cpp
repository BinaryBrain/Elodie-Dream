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
    Mapper::beautify(this->tiles);
}

void Level::draw(GameView* view) {
    for(unsigned int y=0; y<tiles.size(); y++) {
        for(unsigned int x=0; x<tiles[y].size(); x++) {
            if(tiles[y][x]) {
                tiles[y][x]->setPosition(x*32, y*32);
                view->addDrawable(tiles[y][x]);
            }
        }
    }
}
