#include "Overworld.h"

Overworld::Overworld(GameView& gameView, bool muted) : Displayable(gameView)
{

    JsonAccessor worldStructureAcccessor;

    worldStructureAcccessor.loadJsonFrom("assets/config/levels/worldStruct.json");

    subWorldsNumber = worldStructureAcccessor.getInt("subWorldsNumber");

    envsPerSubworld = worldStructureAcccessor.getIntVector("envsPerSubworld");

    levelsPerSubworld = worldStructureAcccessor.getIntVector("levelsPerSubworld");

    fadeTime = worldStructureAcccessor.getDouble("fadeTime");

    for (int w = 0; w < subWorldsNumber; ++w)
    {
        overworldSprites.push_back(std::vector<sf::Sprite>());
        overworldTextures.push_back(std::vector<sf::Texture*>());
        for (int i = 0; i < envsPerSubworld[w]; ++i)
        {
            sf::Texture* overworld = new sf::Texture;
            overworldTextures[w].push_back(overworld);
            overworldTextures[w].back()->loadFromFile("assets/img/overworld/subWorld"+ Utils::itos(w) +"/overworld" + Utils::itos(i) + ".png");
            overworldSprites[w].push_back(sf::Sprite(*(overworldTextures[w].back())));
        }
        JsonAccessor accessor;
        accessor.loadJsonFrom("assets/config/levels/subWorld" + Utils::itos(w) + "/pos.json");

        levelPos.push_back(std::vector< std::vector< int > >());
        for (int i = 0; i < levelsPerSubworld[w]; ++i)
        {
            levelPos[w].push_back(accessor.getIntVector(Utils::itos(i)));
        }

        accessor.loadJsonFrom("assets/config/levels/subWorld" + Utils::itos(w) + "/in.json");

        inPos.push_back(accessor.getIntVector("coord"));
        trigIn.push_back(accessor.getString("trigBy"));

        accessor.loadJsonFrom("assets/config/levels/subWorld" + Utils::itos(w) + "/out.json");

        outPos.push_back(accessor.getIntVector("coord"));
        trigOut.push_back(accessor.getString("trigBy"));


        envs.push_back(std::vector<int>());
        accessor.loadJsonFrom("assets/config/levels/subWorld" + Utils::itos(w) + "/envs.json");
        for (int i = 0; i < levelsPerSubworld[w]; ++i)
        {
            envs[w].push_back(accessor.getInt(Utils::itos(i)));
        }

        levelSpotSprites.push_back(std::vector<sf::Sprite*>());
        for (int i = 0; i < levelsPerSubworld[w]; ++i)
        {
            sf::Texture* spotTexture = new sf::Texture;
            spotTexture->loadFromFile("assets/img/overworld/spot_level_" + Utils::itos(static_cast<int>(getEnvFromLevel({w,i}))) + ".png");
            sf::Sprite* spotSprite = new sf::Sprite(*spotTexture);
            spotSprite->setPosition((levelPos[w][i])[0] - 16, (levelPos[w][i])[1] - 16);
            levelSpotSprites[w].push_back(spotSprite);
        }


        pathSprites.push_back(std::vector<sf::Sprite*>());
        if (w > 0)
        {
            sf::Texture* pathTexture = new sf::Texture;
            pathTexture->loadFromFile("assets/img/overworld/subWorld" + Utils::itos(w) + "/inPath.png");
            sf::Sprite* pathSprite = new sf::Sprite(*pathTexture);
            pathSprite->setPosition(-8, -7);
            pathSprites[w].push_back(pathSprite);
        }
        else
        {
            pathSprites[w].push_back(new sf::Sprite);
        }

        for (int i = 1; i < levelsPerSubworld[w]; ++i)
        {
            sf::Texture* pathTexture = new sf::Texture;
            pathTexture->loadFromFile("assets/img/overworld/subWorld" + Utils::itos(w) + "/path"+Utils::itos(i)+".png");
            sf::Sprite* pathSprite = new sf::Sprite(*pathTexture);
            pathSprite->setPosition(-8, -7);
            pathSprites[w].push_back(pathSprite);
        }

        if (trigOut[w] != "NONE")
        {
            sf::Texture* pathTexture = new sf::Texture;
            pathTexture->loadFromFile("assets/img/overworld/subWorld" + Utils::itos(w) + "/outpath.png");
            sf::Sprite* pathSprite = new sf::Sprite(*pathTexture);
            pathSprite->setPosition(-8, -7);
            pathSprites[w].push_back(pathSprite);
        }

        accessor.loadJsonFrom("assets/config/levels/subWorld" + Utils::itos(w) + "/paths.json");

        paths.push_back(std::vector<sf::VertexArray*>());
        for(size_t i = 0; i < levelPos[w].size(); i++)
        {
            int curPos = -1;

            sf::Vector2f* vec = new sf::Vector2f(-1,-1);
            std::vector<sf::Vector2f*>* mem = new std::vector<sf::Vector2f*>();

            do
            {
                curPos ++;
                std::vector<int> tmp = accessor.getIntVector(Utils::itos(curPos));
                vec = new sf::Vector2f((tmp)[0], (tmp)[1]);
                mem->push_back(vec);
            }
            while ((*vec).x != (levelPos[w][i])[0] or (*vec).y != (levelPos[w][i])[1]);

            sf::VertexArray* path = new sf::VertexArray(sf::LinesStrip, mem->size());

            for (size_t j = 0; j < mem->size(); j++)
            {
                (*path)[j].position = (*(*mem)[j]);
            }

            paths[w].push_back(path);
        }

    }

    float viewX = gameView.getSizeX();
    float viewY = gameView.getSizeY();

    fader.setSize(sf::Vector2f(viewX, viewY));
    fader.setFillColor(sf::Color(0x00, 0x00, 0x00, 0x00));
    fader.setPosition(0, 0);

    currentState.push_back(0);
    currentState.push_back(UNIL1);
    elodie = new Elodie(0,0);
    resetPos();
    if (!music.openFromFile(MUSIC_PATH+"/"+OVERWORLD_MUSIC))
    {
        // TODO Handle error
    }
    else
    {
        music.setLoop(true);
        if (!muted)
        {
            music.play();
        }
    }

    gameView.addView(ViewLayer::OVERWORLD, this);
}


Overworld::~Overworld()
{
    for (size_t i = 0; i < pathSprites.size(); ++i)
    {
        for (std::vector<sf::Sprite*>::iterator sprite = pathSprites[i].begin(); sprite != pathSprites[i].end(); ++sprite)
        {
            delete *sprite;
        }
    }

    for (size_t i = 0; i < overworldTextures.size(); ++i)
    {
        for (std::vector<sf::Texture*>::iterator texture = overworldTextures[i].begin(); texture != overworldTextures[i].end(); ++texture)
        {
            delete *texture;
        }
    }

    for (size_t i = 0; i < levelSpotSprites.size(); i++)
    {
        for (std::vector<sf::Sprite*>::iterator sprite = levelSpotSprites[i].begin(); sprite != levelSpotSprites[i].end(); ++sprite)
        {
            delete *sprite;
        }
    }

    for (size_t i = 0; i < paths.size(); ++ i)
    {
        for (std::vector<sf::VertexArray*>::iterator path = paths[i].begin(); path != paths[i].end(); ++path)
        {
            delete *path;
        }
    }
    delete elodie;
}

void Overworld::resetPos()
{
    if (curSubWorld < (unsigned int) currentState[0])
    {
        elodie->setPosition((* (paths[curSubWorld][ levelsPerSubworld[curSubWorld] - 1]))[curPosInPath].position.x-32,(* (paths[curSubWorld][ levelsPerSubworld[curSubWorld] - 1]))[curPosInPath].position.y-64);
    }
    else
    {
        elodie->setPosition((* (paths[curSubWorld][currentState[1]]))[curPosInPath].position.x-32,(* (paths[curSubWorld][currentState[1]]))[curPosInPath].position.y-64);
    }
}

void Overworld::setPosInPath(int pos)
{
    curPosInPath = pos;
}

void Overworld::display()
{
    if (curSubWorld < (unsigned int) currentState[0])
    {
        gameView.addDrawable(ViewLayer::OVERWORLD, &overworldSprites[curSubWorld][envsPerSubworld[curSubWorld]-1]);
        gameView.addDrawable(ViewLayer::OVERWORLD, pathSprites[curSubWorld][levelsPerSubworld[curSubWorld]]);
        for(size_t i = 0; i < levelSpotSprites[curSubWorld].size(); ++i)
        {
            gameView.addDrawable(ViewLayer::OVERWORLD, levelSpotSprites[curSubWorld][i]);
        }
    }
    else
    {
        gameView.addDrawable(ViewLayer::OVERWORLD, &overworldSprites[curSubWorld][envs[curSubWorld][currentState[1]]]);
        gameView.addDrawable(ViewLayer::OVERWORLD, pathSprites[curSubWorld][currentState[1]]);
        for(int i = 0; i <= currentState[1]; ++i)
        {
            gameView.addDrawable(ViewLayer::OVERWORLD, levelSpotSprites[curSubWorld][i]);
        }
    }
    gameView.addDrawable(ViewLayer::OVERWORLD, elodie->getSprite());
    gameView.addDrawable(ViewLayer::OVERWORLD, &fader);
}

int Overworld::moveUp()
{
    int pathnumber = curSubWorld < (unsigned int) currentState[0] ? levelsPerSubworld[curSubWorld] - 1 : currentState[1];

    sf::Vertex curPos = (* (paths[curSubWorld][pathnumber]))[curPosInPath];
    if(curPosInPath < paths[curSubWorld][pathnumber]->getVertexCount()-1)
    {
        sf::Vertex nextPos = (* (paths[curSubWorld][pathnumber]))[curPosInPath+1];
        if(curPos.position.y > nextPos.position.y)
        {
            curPosInPath++;
            return curPos.position.y - nextPos.position.y;
        }
    }

    if (curPosInPath > 0)
    {
        sf::Vertex prevPos = (* (paths[curSubWorld][pathnumber]))[curPosInPath-1];
        if(curPos.position.y > prevPos.position.y)
        {
            curPosInPath--;
            return curPos.position.y - prevPos.position.y;
        }
    }

    if (curPosInPath == 0 && trigIn[curSubWorld] == "UP")
    {
        Game::getInstance().setState(GameState::PREVOW);
        elodie->setWalkUp();
    }

    if (getLevelFromPath() == (levelsPerSubworld[curSubWorld]-1) && trigOut[curSubWorld] == "UP" && curSubWorld < (size_t) currentState[0])
    {
        Game::getInstance().setState(GameState::NEXTOW);
        elodie->setWalkUp();
    }
    return 0;
}

int Overworld::moveDown()
{
    int pathnumber = curSubWorld < (unsigned int) currentState[0] ? levelsPerSubworld[curSubWorld] - 1 : currentState[1];

    sf::Vertex curPos = (* (paths[curSubWorld][pathnumber]))[curPosInPath];
    if(curPosInPath < paths[curSubWorld][pathnumber]->getVertexCount()-1)
    {
        sf::Vertex nextPos = (* (paths[curSubWorld][pathnumber]))[curPosInPath+1];
        if(curPos.position.y < nextPos.position.y)
        {
            curPosInPath++;
            return nextPos.position.y - curPos.position.y;
        }
    }

    if (curPosInPath > 0)
    {
        sf::Vertex prevPos = (* (paths[curSubWorld][pathnumber]))[curPosInPath-1];
        if(curPos.position.y < prevPos.position.y)
        {
            curPosInPath--;
            return prevPos.position.y - curPos.position.y;
        }
    }

    if (curPosInPath == 0 && trigIn[curSubWorld] == "DOWN")
    {
        Game::getInstance().setState(GameState::PREVOW);
        elodie->setWalkDown();
    }

    if (getLevelFromPath() == (levelsPerSubworld[curSubWorld]-1) && trigOut[curSubWorld] == "DOWN" && curSubWorld < (size_t) currentState[0])
    {
        Game::getInstance().setState(GameState::NEXTOW);
        elodie->setWalkDown();
    }

    return 0;
}

int Overworld::moveRight()
{
    int pathnumber = curSubWorld < (unsigned int) currentState[0] ? levelsPerSubworld[curSubWorld] - 1 : currentState[1];
    sf::Vertex curPos = (* (paths[curSubWorld][pathnumber]))[curPosInPath];
    if(curPosInPath < paths[curSubWorld][pathnumber]->getVertexCount()-1)
    {
        sf::Vertex nextPos = (* (paths[curSubWorld][pathnumber]))[curPosInPath+1];
        if(curPos.position.x < nextPos.position.x)
        {
            curPosInPath++;
            return nextPos.position.x - curPos.position.x;
        }
    }

    if (curPosInPath > 0)
    {
        sf::Vertex prevPos = (* (paths[curSubWorld][pathnumber]))[curPosInPath-1];
        if(curPos.position.x < prevPos.position.x)
        {
            curPosInPath--;
            return prevPos.position.x - curPos.position.x;
        }
    }

    if (curPosInPath == 0 && trigIn[curSubWorld] == "RIGHT")
    {
        Game::getInstance().setState(GameState::PREVOW);
        elodie->setWalkRight();
    }

    if (getLevelFromPath() ==  (levelsPerSubworld[curSubWorld]-1) && trigOut[curSubWorld] == "RIGHT" && curSubWorld < (size_t) currentState[0])
    {
        Game::getInstance().setState(GameState::NEXTOW);
        elodie->setWalkRight();
    }

    return 0;
}

int Overworld::moveLeft()
{
    int pathnumber = curSubWorld < (unsigned int) currentState[0] ? levelsPerSubworld[curSubWorld] - 1 : currentState[1];
    sf::Vertex curPos = (* (paths[curSubWorld][pathnumber]))[curPosInPath];
    if(curPosInPath < paths[curSubWorld][pathnumber]->getVertexCount()-1)
    {
        sf::Vertex nextPos = (* (paths[curSubWorld][pathnumber]))[curPosInPath+1];
        if(curPos.position.x > nextPos.position.x)
        {
            curPosInPath++;
            return curPos.position.x - nextPos.position.x;
        }
    }

    if (curPosInPath > 0)
    {
        sf::Vertex prevPos = (* (paths[curSubWorld][pathnumber]))[curPosInPath-1];
        if(curPos.position.x > prevPos.position.x)
        {
            curPosInPath--;
            return curPos.position.x - prevPos.position.x;
        }
    }
    if (curPosInPath == 0 && trigIn[curSubWorld] == "LEFT")
    {
        Game::getInstance().setState(GameState::PREVOW);
        elodie->setWalkLeft();
    }

    if (getLevelFromPath() ==  (levelsPerSubworld[curSubWorld]-1) && trigOut[curSubWorld] == "LEFT" && curSubWorld < (size_t) currentState[0])
    {
        Game::getInstance().setState(GameState::NEXTOW);
        elodie->setWalkLeft();
    }
    return 0;
}

void Overworld::evolve(std::vector<int> succLevel)
{
    if (succLevel[0] >= currentState[0] )
    {
        if (succLevel[1] >= currentState[1])
        {
            if (succLevel[1] < levelsPerSubworld[currentState[0]] - 1)
            {
                currentState[1] = succLevel[1] + 1;
            }
            else if (currentState[0] < subWorldsNumber - 1)
            {
                currentState[0] += 1;
                currentState[1] = 0;
            }
        }
    }
}

Elodie& Overworld::getElodie()
{
    return *elodie;
}

int Overworld::getCurrentEnv()
{
    return (int)currentState[1];
}

unsigned int Overworld::getCurrentSubworld() {
    return curSubWorld;
}

sf::Music& Overworld::getMusic()
{
    return music;
}

std::vector<int> Overworld::getLevelToLoad()
{
    std::vector<int> toReturn;
    toReturn.push_back(curSubWorld);
    toReturn.push_back(getLevelFromPath());
    return toReturn;
}

const std::vector<int>& Overworld::getLevelsPerSubworld()
{
    return levelsPerSubworld;
}

const std::vector<int>& Overworld::getState()
{
    return currentState;
}

void Overworld::setState(std::vector<int> state)
{
    currentState[0] = state[0];
    currentState[1] = state[1];
}

void Overworld::setToLevel(std::vector<int> level)
{
    if (level[0] < subWorldsNumber)
    {
        curSubWorld = (unsigned int) level[0];
    }

    if (level[1] < levelsPerSubworld[curSubWorld])
    {
        std::vector<int> wantedPos = levelPos[curSubWorld][level[1]];
        sf::VertexArray path = (* (paths[curSubWorld][currentState[1]]));
        bool found = false;
        size_t i = 0;
        while (!found)
        {
            if (path[i].position.x == wantedPos[0] && path[i].position.y == wantedPos[1])
            {
                found = true;
                curPosInPath = i;
            }
            else
            {
                ++i;
            }
        }
    }
}

void Overworld::nextOverWorld()
{
    curPosInPath = 0;
    curSubWorld++;
    resetPos();
}

void Overworld::prevOverWorld()
{
    curSubWorld--;
    std::vector<int> wantedPos = levelPos[curSubWorld][levelsPerSubworld[curSubWorld]-1];
    sf::VertexArray path = (* (paths[curSubWorld][levelsPerSubworld[curSubWorld]-1]));
    bool found = false;
    size_t i = 0;
    while (!found)
    {
        if (path[i].position.x == wantedPos[0] && path[i].position.y == wantedPos[1])
        {
            found = true;
            curPosInPath = i;
        }
        else
        {
            ++i;
        }
    }

    resetPos();
}

int Overworld::getLevelFromPath()
{
    int pathnumber = curSubWorld < (unsigned int) currentState[0] ? levelsPerSubworld[curSubWorld] - 1 : currentState[1];
    sf::Vertex curPos = (* (paths[curSubWorld][pathnumber]))[curPosInPath];
    for (size_t i = 0; i < levelPos[curSubWorld].size(); ++i)
    {
        if(levelPos[curSubWorld][i][0] == curPos.position.x && levelPos[curSubWorld][i][1] == curPos.position.y)
        {
            return i;
        }
    }
    return -1;
}

LevelEnv Overworld::getEnvFromLevel(std::vector<int> level)
{
    int finalRes = 0;

    for (size_t i = 0; i < (size_t) level[0]; ++i)
    {
        finalRes += envsPerSubworld[i];
    }

    finalRes += envs[level[0]][level[1]];
    return static_cast<LevelEnv>(finalRes);
}

void Overworld::incFaderAlpha()
{
    int actAlpha = getFaderAlpha();
    double incframes = (FPS * fadeTime)/2.0;
    int increment = (int) 255/incframes;
    //std::cout << Utils::itos(increment) << std::endl;
    int newAlpha = (actAlpha + increment) > 255 ? 255 : (actAlpha + increment);
    fader.setFillColor(sf::Color(0x00, 0x00, 0x00, newAlpha));
}

void Overworld::decFaderAlpha()
{
    int actAlpha = getFaderAlpha();
    double incframes = (FPS * fadeTime)/2.0;
    int increment = (int) 255/incframes;
    int newAlpha = (actAlpha - increment) < 0 ? 0 : (actAlpha - increment);
    fader.setFillColor(sf::Color(0x00, 0x00, 0x00, newAlpha));
}

int Overworld::getFaderAlpha()
{
    return fader.getFillColor().a;
}

std::vector<int> Overworld::getInPos()
{
    return inPos[curSubWorld];
}

std::vector<int> Overworld::getOutPos()
{
    return outPos[curSubWorld];
}

std::string Overworld::getTrigIn()
{
    return trigIn[curSubWorld];
}
std::string Overworld::getTrigOut()
{
    return trigOut[curSubWorld];
}

void Overworld::printCoord(std::vector<int> coord)
{
    std::cout << "(" << coord[0] << ", " << coord[1] << ")" << std::endl;
}
