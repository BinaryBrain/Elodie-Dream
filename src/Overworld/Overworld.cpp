#include "Overworld.h"

Overworld::Overworld() {
    std::string filenames[4] = { "overworld1.png", "overworld2.png", "overworld3.png", "overworld4.png" };

    for(int i=0; i<4; i++) {
        sf::Texture* overworld = new sf::Texture;
        overworld->loadFromFile("assets/img/overworld/"+filenames[i]);
        overworldSprites.push_back(new sf::Sprite(*overworld));
    }

    JsonAccessor lvlPos = JsonAccessor();
    lvlPos.load("assets/config/levels/levelPos.lvl");

    levelPos.push_back(lvlPos.getIntVector("unil"));
    levelPos.push_back(lvlPos.getIntVector("castle"));
    levelPos.push_back(lvlPos.getIntVector("volcano"));
    levelPos.push_back(lvlPos.getIntVector("freljord"));

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

    elodie = new Elodie(565,643);
    currentState = UNIL;
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

sf::Sprite* Overworld::getCurrentSprite() {
    return overworldSprites[currentState];
}

Elodie* Overworld::getElodie() {
    return elodie;
}

sf::VertexArray* Overworld::getPath() {
    return paths[currentState];
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
