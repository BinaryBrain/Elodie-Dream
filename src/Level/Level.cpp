#include "Level.h"

Level::Level(GameView* gameView, std::string filename, LevelEnv env, Elodie* elodie) : Displayable(gameView)  {
    this->environement = env;
    this->manager = new TextureManager();

    loadLevel(filename, elodie);
    gameView->addView(ViewLayer::LEVEL, this);
    gameView->setZoom(ViewLayer::LEVEL, ZOOM_LEVEL);

    gameView->setCameraCenter(ViewLayer::LEVEL, elodie->getPosition());

    if (!music.openFromFile(MUSIC_PATH+"/"+LEVEL_MUSIC)) {
        // TODO Handle error
    } else {
        music.setLoop(true);

        Game* game = Game::getInstance();
        if(!game->isMute()) {
            music.play();
        }
    }

}

Level::~Level() {
    for(size_t i(0); i < tiles.size(); ++i) {
        for(size_t j(0); j < tiles[i].size(); ++j) {
            delete tiles[i][j];
        }
    }

    for(EntityMap::iterator it = entities.begin(); it != entities.end(); ++it) {
        if(it->first.compare("elodie")) {
            delete it->second;
        }
    }

    delete this->manager;
}

void Level::setEnvironement(LevelEnv env) {
    this->environement = env;
}

// Load a level from the file system
void Level::loadLevel(std::string filename, Elodie* elodie) {
    std::string levelSource = FileHandler::getContent(filename);

    Mapper::parse(levelSource, tiles, entities, elodie);
    Mapper::beautify(tiles);

    applyEnv(tiles);
}

// Ask the given view to draw a Level frame
void Level::display() {
    for(unsigned int y=0; y<tiles.size(); y++) {
        for(unsigned int x=0; x<tiles[y].size(); x++) {
            if(tiles[y][x]) {
                tiles[y][x]->setPosition(x*32, y*32);
                gameView->addDrawable(ViewLayer::LEVEL, tiles[y][x]);
            }
        }
    }

    for(EntityMap::iterator entity_ptr = entities.begin(); entity_ptr != entities.end(); ++entity_ptr) {
        Entity* entity = entity_ptr->second;
        sf::Sprite* sprite = entity->getSprite();

        if(sprite) {
            gameView->addDrawable(ViewLayer::LEVEL, sprite);
        }
    }

    Elodie* elodie = dynamic_cast<Elodie*>(entities["elodie"]);
    gameView->followPoint(ViewLayer::LEVEL, elodie->getCameraPos());
}

void Level::live(EventHandler* const& event, sf::Time animate) {
    std::vector< std::string > toDelete;
    Elodie* elodie = dynamic_cast<Elodie*>(entities["elodie"]);
    sf::FloatRect scope(0, 0, LIVE_SCOPE, LIVE_SCOPE);
    scope.top = ((Elodie*)entities["elodie"])->getPosition().y - LIVE_SCOPE / 2;
    scope.left = ((Elodie*)entities["elodie"])->getPosition().x - LIVE_SCOPE / 2;
    entities["elodie"]->doStuff(event, tiles, entities, animate);
    for (EntityMap::iterator it = entities.begin(); it != entities.end(); ++it) {
        if (it->first != "elodie" && scope.intersects(it->second->returnCurrentHitbox().getArea())) {
            it->second->doStuff(event, tiles, entities, animate);
            if (!it->second->isAlive()) {
                toDelete.push_back(it->first);
            }
        }
    }
    for (unsigned int i = 0; i < toDelete.size(); ++i) {
        delete entities[toDelete[i]];
        entities.erase(toDelete[i]);
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

void Level::play(sf::Clock *frameClock) {
    entities["elodie"]->play();
    frameClock->restart();
}

sf::Music* Level::getMusic() {
    return &music;
}

bool Level::mustDie() {
    Elodie* elodie = dynamic_cast<Elodie*>(entities["elodie"]);
    bool test1 = gameView->isPointOutsideView(ViewLayer::LEVEL, elodie->getPosition().x, elodie->getPosition().y);
    bool test2 = elodie->getImmersionLevel() <= 0;
    return test1 || test2;
}
