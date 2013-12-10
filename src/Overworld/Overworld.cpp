#include "Overworld.h"

Overworld::Overworld(GameView* gameView) : Displayable(gameView) {
    std::string filenames[4] = { "overworld1.png", "overworld2.png", "overworld3.png", "overworld4.png" };

    for(int i=0; i<4; i++) {
        sf::Texture* overworld = new sf::Texture;
        overworld->loadFromFile("assets/img/overworld/"+filenames[i]);
        overworldSprites.push_back(new sf::Sprite(*overworld));
    }

    JsonAccessor lvlPos = JsonAccessor();
    lvlPos.load("assets/config/levels/levelPos.lvl");

    //levelPos.push_back(lvlPos.getIntVector(LEVELENV_FIELD));
    levelPos.push_back(lvlPos.getIntVector(LEVELENV_UNIL));
    levelPos.push_back(lvlPos.getIntVector(LEVELENV_CASTLE));
    levelPos.push_back(lvlPos.getIntVector(LEVELENV_VOLCANO));
    levelPos.push_back(lvlPos.getIntVector(LEVELENV_FRELJORD));

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

    currentState = UNIL;
    elodie = new Elodie(0,0);
    resetPos();

    if (!music.openFromFile(MUSIC_PATH+"/"+OVERWORLD_MUSIC)) {
        // TODO Handle error
    } else {
        music.setLoop(true);

        music.play();
    }
}


Overworld::~Overworld() {
    for (std::vector<sf::Sprite*>::iterator sprite = overworldSprites.begin(); sprite != overworldSprites.end(); ++sprite) {
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
    elodie->setPosition((* (paths[currentState]))[curPosInPath].position.x - 40,(* (paths[currentState]))[curPosInPath].position.y - 40);
}

void Overworld::display() {
    gameView->addDrawable(ViewLayer::OVERWORLD, overworldSprites[currentState]);
    gameView->addDrawable(ViewLayer::OVERWORLD, elodie->getSprite());
    gameView->addDrawable(ViewLayer::OVERWORLD, paths[currentState]);
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

void Overworld::evolve() {
    switch(currentState) {
    case UNIL:
        currentState = CASTLE;
        break;
    case CASTLE:
        currentState = VOLCANO;
        break;
    case VOLCANO:
        currentState = FRELJORD;
        break;
        // FIXME Dev stuff
    case FRELJORD:
        currentState = UNIL;
        break;
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
