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
        this->paths.push_back(path);
    }

    this->elodie = new Elodie(565,643);
    this->currentState = UNIL;
}

Overworld::~Overworld() {
    for (std::vector<sf::Sprite*>::iterator sprite = this->overworldSprites.begin(); sprite != this->overworldSprites.end(); ++sprite) {
        delete *sprite;
    }
    for (std::vector<std::vector<int>*>::iterator pos = this->levelPos.begin(); pos != this->levelPos.end(); ++pos) {
        delete *pos;
    }
    for (std::vector<sf::VertexArray*>::iterator path = this->paths.begin(); path != this->paths.end(); ++path) {
        delete *path;
    }
    delete this->elodie;
}

int Overworld::moveUp() {
    sf::Vertex curPos = (* (this->paths[this->currentState]))[curPosInPath];
    if(curPosInPath < this->paths[this->currentState]->getVertexCount()-1) {
        sf::Vertex nextPos = (* (this->paths[this->currentState]))[curPosInPath+1];
        if(curPos.position.y > nextPos.position.y) {
            curPosInPath++;
            return curPos.position.y - nextPos.position.y;
        }
    }

    if (curPosInPath > 0) {
        sf::Vertex prevPos = (* (this->paths[this->currentState]))[curPosInPath-1];
        if(curPos.position.y > prevPos.position.y) {
            curPosInPath--;
            return curPos.position.y - prevPos.position.y;
        }
    }

    return 0;
}

int Overworld::moveDown() {
    sf::Vertex curPos = (* (this->paths[this->currentState]))[curPosInPath];
    if(curPosInPath < this->paths[this->currentState]->getVertexCount()-1) {
        sf::Vertex nextPos = (* (this->paths[this->currentState]))[curPosInPath+1];
        if(curPos.position.y < nextPos.position.y) {
            curPosInPath++;
            return nextPos.position.y - curPos.position.y;
        }
    }

    if (curPosInPath > 0) {
        sf::Vertex prevPos = (* (this->paths[this->currentState]))[curPosInPath-1];
        if(curPos.position.y < prevPos.position.y) {
            curPosInPath--;
            return prevPos.position.y - curPos.position.y;
        }
    }

    return 0;
}

int Overworld::moveRight() {
    sf::Vertex curPos = (* (this->paths[this->currentState]))[curPosInPath];
    if(curPosInPath < this->paths[this->currentState]->getVertexCount()-1) {
        sf::Vertex nextPos = (* (this->paths[this->currentState]))[curPosInPath+1];
        if(curPos.position.x < nextPos.position.x) {
            curPosInPath++;
            return nextPos.position.x - curPos.position.x;
        }
    }

    if (curPosInPath > 0) {
        sf::Vertex prevPos = (* (this->paths[this->currentState]))[curPosInPath-1];
        if(curPos.position.x < prevPos.position.x) {
            curPosInPath--;
            return prevPos.position.x - curPos.position.x;
        }
    }

    return 0;
}

int Overworld::moveLeft() {
    sf::Vertex curPos = (* (this->paths[this->currentState]))[curPosInPath];
    if(curPosInPath < this->paths[this->currentState]->getVertexCount()-1) {
        sf::Vertex nextPos = (* (this->paths[this->currentState]))[curPosInPath+1];
        if(curPos.position.x > nextPos.position.x) {
            curPosInPath++;
            return curPos.position.x - nextPos.position.x;
        }
    }

    if (curPosInPath > 0) {
        sf::Vertex prevPos = (* (this->paths[this->currentState]))[curPosInPath-1];
        if(curPos.position.x > prevPos.position.x) {
            curPosInPath--;
            return curPos.position.x - prevPos.position.x;
        }
    }

    return 0;
}

sf::Sprite* Overworld::getCurrentSprite() {
    return this->overworldSprites[this->currentState];
}

Elodie* Overworld::getElodie() {
    return this->elodie;
}

sf::VertexArray* Overworld::getPath() {
    return this->paths[this->currentState];
}

void Overworld::evolve() {
    switch(this->currentState) {
    case UNIL:
        this->currentState = CASTLE;
        break;
    case CASTLE:
        this->currentState = VOLCANO;
        break;
    case VOLCANO:
        this->currentState = FRELJORD;
        break;
        // FIXME Dev stuff
    case FRELJORD:
        this->currentState = UNIL;
        break;
    default:
        break;
    }
}
