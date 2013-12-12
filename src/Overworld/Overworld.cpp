#include "Overworld.h"

Overworld::Overworld(GameView* gameView, bool muted) : Displayable(gameView) {
    std::string filenames[4] = { "overworld1.png", "overworld2.png", "overworld3.png", "overworld4.png" };

    for(int i=0; i<4; i++) {
        sf::Texture* overworld = new sf::Texture;
        overworld->loadFromFile("assets/img/overworld/"+filenames[i]);
        overworldSprites.push_back(new sf::Sprite(*overworld));
    }

    JsonAccessor lvlPos = JsonAccessor();
    lvlPos.load("assets/config/levels/levelPos.lvl");

    //levelPos.push_back(lvlPos.getIntVector(LEVELENV_FIELD));
    levelPos.push_back(lvlPos.getIntVector(LEVELENV_UNIL + "1"));
    levelPos.push_back(lvlPos.getIntVector(LEVELENV_UNIL + "2"));
    levelPos.push_back(lvlPos.getIntVector(LEVELENV_CASTLE + "1"));
    levelPos.push_back(lvlPos.getIntVector(LEVELENV_CASTLE + "2"));
    levelPos.push_back(lvlPos.getIntVector(LEVELENV_VOLCANO + "1"));
    levelPos.push_back(lvlPos.getIntVector(LEVELENV_VOLCANO + "2"));
    levelPos.push_back(lvlPos.getIntVector(LEVELENV_FRELJORD + "1"));
    levelPos.push_back(lvlPos.getIntVector(LEVELENV_FRELJORD + "2"));

    for (size_t i = 0; i < 8; ++i) {
        sf::Texture* spotTexture = new sf::Texture;
        spotTexture->loadFromFile("assets/img/overworld/spot_level.png");
        sf::Sprite* spotSprite = new sf::Sprite(*spotTexture);
        spotSprite->setPosition((*levelPos[i])[0] - 16, (*levelPos[i])[1] - 16);
        levelSpotSprites.push_back(spotSprite);
    }
    pathSprites.push_back(new sf::Sprite);
    for (size_t i = 1; i < 8; ++i) {
        sf::Texture* pathTexture = new sf::Texture;
        pathTexture->loadFromFile("assets/img/overworld/path"+Utils::itos(i)+".png");
        sf::Sprite* pathSprite = new sf::Sprite(*pathTexture);
        pathSprite->setPosition(-8, -7);
        pathSprites.push_back(pathSprite);
    }

    JsonAccessor lvlPaths;
    lvlPaths.load("assets/config/levels/levelPaths.lvl");

    for(size_t i = 0; i < levelPos.size(); i++) {
        int curPos = -1;

        sf::Vector2f* vec = new sf::Vector2f(-1,-1);
        std::vector<sf::Vector2f*>* mem = new std::vector<sf::Vector2f*>();

        do {
            curPos ++;
            std::vector<int>* tmp = lvlPaths.getIntVector(Utils::itos(curPos));
            vec = new sf::Vector2f((*tmp)[0], (*tmp)[1]);
            mem->push_back(vec);
        } while ((*vec).x != (*levelPos[i])[0] or (*vec).y != (*levelPos[i])[1]);

        sf::VertexArray* path = new sf::VertexArray(sf::LinesStrip, mem->size());

        for (size_t j = 0; j < mem->size(); j++) {
            (*path)[j].position = (*(*mem)[j]);
        }

        paths.push_back(path);
    }

    currentState = UNIL1;
    elodie = new Elodie(0,0);
    resetPos();

    if (!music.openFromFile(MUSIC_PATH+"/"+OVERWORLD_MUSIC)) {
        // TODO Handle error
    } else {
        music.setLoop(true);
        if (!muted) {
            music.play();
        }
    }
}


Overworld::~Overworld() {
    for (std::vector<sf::Sprite*>::iterator sprite = pathSprites.begin(); sprite != pathSprites.end(); ++sprite) {
        delete *sprite;
    }
    for (std::vector<sf::Sprite*>::iterator sprite = overworldSprites.begin(); sprite != overworldSprites.end(); ++sprite) {
        delete *sprite;
    }

    for (std::vector<sf::Sprite*>::iterator sprite = levelSpotSprites.begin(); sprite != levelSpotSprites.end(); ++sprite) {
        delete *sprite;
    }

    for (std::vector<std::vector<int>*>::iterator pos = levelPos.begin(); pos != levelPos.end(); ++pos) {
        delete *pos;
    }
    for (std::vector<sf::VertexArray*>::iterator path = paths.begin(); path != paths.end(); ++path) {
        delete *path;
    }
    delete elodie;
}

void Overworld::resetPos() {
    elodie->setPosition((* (paths[currentState]))[curPosInPath].position.x-32,(* (paths[currentState]))[curPosInPath].position.y-64);
}

void Overworld::display() {
    gameView->addDrawable(ViewLayer::OVERWORLD, overworldSprites[whichOverworld()]);
    gameView->addDrawable(ViewLayer::OVERWORLD, pathSprites[currentState]);
    for(size_t i = 0; i <= currentState; ++i) {
        gameView->addDrawable(ViewLayer::OVERWORLD, levelSpotSprites[i]);
    }
    gameView->addDrawable(ViewLayer::OVERWORLD, elodie->getSprite());
}

int Overworld::moveUp() {
    sf::Vertex curPos = (* (paths[currentState]))[curPosInPath];
    if(curPosInPath < paths[currentState]->getVertexCount()-1) {
        sf::Vertex nextPos = (* (paths[currentState]))[curPosInPath+1];
        if(curPos.position.y > nextPos.position.y) {
            curPosInPath++;
            return curPos.position.y - nextPos.position.y;
        }
    }

    if (curPosInPath > 0) {
        sf::Vertex prevPos = (* (paths[currentState]))[curPosInPath-1];
        if(curPos.position.y > prevPos.position.y) {
            curPosInPath--;
            return curPos.position.y - prevPos.position.y;
        }
    }

    return 0;
}

int Overworld::moveDown() {
    sf::Vertex curPos = (* (paths[currentState]))[curPosInPath];
    if(curPosInPath < paths[currentState]->getVertexCount()-1) {
        sf::Vertex nextPos = (* (paths[currentState]))[curPosInPath+1];
        if(curPos.position.y < nextPos.position.y) {
            curPosInPath++;
            return nextPos.position.y - curPos.position.y;
        }
    }

    if (curPosInPath > 0) {
        sf::Vertex prevPos = (* (paths[currentState]))[curPosInPath-1];
        if(curPos.position.y < prevPos.position.y) {
            curPosInPath--;
            return prevPos.position.y - curPos.position.y;
        }
    }

    return 0;
}

int Overworld::moveRight() {
    sf::Vertex curPos = (* (paths[currentState]))[curPosInPath];
    if(curPosInPath < paths[currentState]->getVertexCount()-1) {
        sf::Vertex nextPos = (* (paths[currentState]))[curPosInPath+1];
        if(curPos.position.x < nextPos.position.x) {
            curPosInPath++;
            return nextPos.position.x - curPos.position.x;
        }
    }

    if (curPosInPath > 0) {
        sf::Vertex prevPos = (* (paths[currentState]))[curPosInPath-1];
        if(curPos.position.x < prevPos.position.x) {
            curPosInPath--;
            return prevPos.position.x - curPos.position.x;
        }
    }

    return 0;
}

int Overworld::moveLeft() {
    sf::Vertex curPos = (* (paths[currentState]))[curPosInPath];
    if(curPosInPath < paths[currentState]->getVertexCount()-1) {
        sf::Vertex nextPos = (* (paths[currentState]))[curPosInPath+1];
        if(curPos.position.x > nextPos.position.x) {
            curPosInPath++;
            return curPos.position.x - nextPos.position.x;
        }
    }

    if (curPosInPath > 0) {
        sf::Vertex prevPos = (* (paths[currentState]))[curPosInPath-1];
        if(curPos.position.x > prevPos.position.x) {
            curPosInPath--;
            return curPos.position.x - prevPos.position.x;
        }
    }

    return 0;
}

void Overworld::evolve(int minLevel, int maxLevel) {
    maxLevel = minLevel > maxLevel ? minLevel : maxLevel;
    switch(currentState) {
    case states::UNIL1:
        currentState = states::UNIL2;
        break;
    case states::UNIL2:
        currentState = states::CASTLE1;
        break;
    case states::CASTLE1:
        currentState = states::CASTLE2;
        break;
    case states::CASTLE2:
        currentState = states::VOLCANO1;
        break;
    case states::VOLCANO1:
        currentState = states::VOLCANO2;
        break;
    case states::VOLCANO2:
        currentState = states::FRELJORD1;
        break;
    case states::FRELJORD1:
        currentState = states::FRELJORD2;
        break;
    default:
        break;
    }

    currentState = (int)currentState > maxLevel ? (states) maxLevel : currentState;
}

int Overworld::whichOverworld() {
    switch(currentState) {
    case states::UNIL1:
        return 0;
    case states::UNIL2:
        return 0;
    case states::CASTLE1:
        return 1;
    case states::CASTLE2:
        return 1;
    case states::VOLCANO1:
        return 2;
    case states::VOLCANO2:
        return 2;
    case states::FRELJORD1:
        return 3;
    case states::FRELJORD2:
        return 3;
    default:
        break;
    }
}

Elodie* Overworld::getElodie() {
    return elodie;
}

int Overworld::getCurrentEnv() {
    return (int)currentState;
}

sf::Music* Overworld::getMusic() {
    return &music;
}

int Overworld::getLevelToLoad() {
    if(curPosInPath == 0) {
        return 0;
    } else if (curPosInPath == 1) {
        return 1;
    } else if (curPosInPath == 3) {
        return 2;
    } else if (curPosInPath == 4) {
        return 3;
    } else if (curPosInPath == 5) {
        return 4;
    } else if (curPosInPath == 7) {
        return 5;
    } else if (curPosInPath == 8) {
        return 6;
    } else if (curPosInPath == 10) {
        return 7;
    } else {
        return -1;
    }
}

int Overworld::getState() {
    return currentState;
}

void Overworld::setState(int state) {
    this->currentState = static_cast<states>(state);
}
