#include "Level.h"

Level::Level(std::string filename, LevelEnv env) {
    loadLevel(filename);
    this->environement = env;
    this->manager = new TextureManager();
}

Level::~Level() {
    for(size_t i(0); i < tiles.size(); ++i){
        for(size_t j(0); j < tiles[i].size(); ++j){
            delete tiles[i][j];
        }
    }

    for(EntityMap::iterator it = entities.begin(); it != entities.end(); ++it){
        delete it->second;
    }
}

void Level::setEnvironement(LevelEnv env) {
    this->environement = env;
}

// Load a level from the file system
void Level::loadLevel(std::string filename) {
    std::string levelSource = FileHandler::getContent(filename);

    Mapper::parse(levelSource, tiles, entities);
    Mapper::beautify(tiles);

    applyEnv(tiles);
}

// Ask the given view to draw a Level frame
void Level::display(GameView* view) {
    for(unsigned int y=0; y<tiles.size(); y++) {
        for(unsigned int x=0; x<tiles[y].size(); x++) {
            if(tiles[y][x]) {
                tiles[y][x]->setPosition(x*32, y*32);
                view->addDrawable(ViewLayer::LEVEL, tiles[y][x]);
            }
        }
    }

    for(EntityMap::iterator entity_ptr = entities.begin(); entity_ptr != entities.end(); ++entity_ptr) {
        Entity* entity = entity_ptr->second;
        sf::Sprite* sprite = entity->getSprite();

        if(sprite) {
            view->addDrawable(ViewLayer::LEVEL, sprite);
        }
    }

    Elodie* elodie = dynamic_cast<Elodie*>(entities["elodie"]);
    view->setFollowedPoint(ViewLayer::LEVEL, elodie->getPosition());
    //view->setSize(160, 100);
}

void Level::live(EventHandler* const& event, sf::Time animate) {
    for (EntityMap::iterator it = entities.begin(); it != entities.end(); ++it) {
        it->second->doStuff(event, tiles, animate);
    }
}

EntityMap Level::getEntities() {
    EntityMap entitiesCpy;

    for (EntityMap::iterator it = entities.begin(); it != entities.end(); ++it) {
        entitiesCpy.insert(std::make_pair(it->first, it->second));
    }
    return entitiesCpy;
}

void Level::applyEnv(TileMap tiles) {
    for(unsigned int y=0; y<tiles.size(); y++) {
        for(unsigned int x=0; x<tiles[y].size(); x++) {
            if(tiles[y][x]) {
                sf::Texture* texture = manager->getTileTexture(environement, tiles[y][x]->getType());
                tiles[y][x]->setTexture(*texture);
            }
        }
    }
}

void Level::pause() {
    entities["elodie"]->pause();
}

void Level::play() {
    entities["elodie"]->play();
}
