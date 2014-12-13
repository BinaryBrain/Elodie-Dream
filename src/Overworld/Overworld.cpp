#include "Overworld.h"

Overworld::Overworld(GameView& gameView, bool muted) : Displayable(gameView)
{

    JsonAccessor worldStructureAcccessor;

    worldStructureAcccessor.loadJsonFrom("assets/config/levels/worldStruct.json");

    subWorldsNumber = worldStructureAcccessor.getInt("subWorldsNumber");

    std::vector<int> envsPerSubworld = worldStructureAcccessor.getIntVector("envsPerSubworld");

    levelsPerSubworld = worldStructureAcccessor.getIntVector("levelsPerSubworld");

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

        levelSpotSprites.push_back(std::vector<sf::Sprite*>());
        for (int i = 0; i < levelsPerSubworld[w]; ++i)
        {
            sf::Texture* spotTexture = new sf::Texture;
            spotTexture->loadFromFile("assets/img/overworld/spot_level.png");
            sf::Sprite* spotSprite = new sf::Sprite(*spotTexture);
            spotSprite->setPosition((levelPos[w][i])[0] - 16, (levelPos[w][i])[1] - 16);
            levelSpotSprites[w].push_back(spotSprite);
        }


        pathSprites.push_back(std::vector<sf::Sprite*>());
        pathSprites[w].push_back(new sf::Sprite);

        for (int i = 1; i < levelsPerSubworld[w]; ++i)
        {
            sf::Texture* pathTexture = new sf::Texture;
            pathTexture->loadFromFile("assets/img/overworld/subWorld" + Utils::itos(w) + "/path"+Utils::itos(i)+".png");
            sf::Sprite* pathSprite = new sf::Sprite(*pathTexture);
            pathSprite->setPosition(-8, -7);
            pathSprites[w].push_back(pathSprite);
        }

        accessor.loadJsonFrom("assets/config/levels/subWorld" + Utils::itos(w) + "/paths.json");

        paths.push_back(std::vector<sf::VertexArray*>());
        unsigned int pathNumber = levelPos[w].size();
        for(size_t i = 0; i < pathNumber; i++)
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
    elodie->setPosition((* (paths[curSubWorld][currentState[1]]))[curPosInPath].position.x-32,(* (paths[curSubWorld][currentState[1]]))[curPosInPath].position.y-64);
}

void Overworld::setPosInPath(int pos)
{
    curPosInPath = pos;
}

void Overworld::display()
{
    gameView.addDrawable(ViewLayer::OVERWORLD, &overworldSprites[curSubWorld][whichOverworld()]);
    gameView.addDrawable(ViewLayer::OVERWORLD, pathSprites[curSubWorld][currentState[1]]);
    for(int i = 0; i <= currentState[1]; ++i)
    {
        gameView.addDrawable(ViewLayer::OVERWORLD, levelSpotSprites[curSubWorld][i]);
    }
    gameView.addDrawable(ViewLayer::OVERWORLD, elodie->getSprite());
}

int Overworld::moveUp()
{
    sf::Vertex curPos = (* (paths[curSubWorld][currentState[1]]))[curPosInPath];
    if(curPosInPath < paths[curSubWorld][currentState[1]]->getVertexCount()-1)
    {
        sf::Vertex nextPos = (* (paths[curSubWorld][currentState[1]]))[curPosInPath+1];
        if(curPos.position.y > nextPos.position.y)
        {
            curPosInPath++;
            return curPos.position.y - nextPos.position.y;
        }
    }

    if (curPosInPath > 0)
    {
        sf::Vertex prevPos = (* (paths[curSubWorld][currentState[1]]))[curPosInPath-1];
        if(curPos.position.y > prevPos.position.y)
        {
            curPosInPath--;
            return curPos.position.y - prevPos.position.y;
        }
    }

    return 0;
}

int Overworld::moveDown()
{
    sf::Vertex curPos = (* (paths[curSubWorld][currentState[1]]))[curPosInPath];
    if(curPosInPath < paths[curSubWorld][currentState[1]]->getVertexCount()-1)
    {
        sf::Vertex nextPos = (* (paths[curSubWorld][currentState[1]]))[curPosInPath+1];
        if(curPos.position.y < nextPos.position.y)
        {
            curPosInPath++;
            return nextPos.position.y - curPos.position.y;
        }
    }

    if (curPosInPath > 0)
    {
        sf::Vertex prevPos = (* (paths[curSubWorld][currentState[1]]))[curPosInPath-1];
        if(curPos.position.y < prevPos.position.y)
        {
            curPosInPath--;
            return prevPos.position.y - curPos.position.y;
        }
    }

    return 0;
}

int Overworld::moveRight()
{
    sf::Vertex curPos = (* (paths[curSubWorld][currentState[1]]))[curPosInPath];
    if(curPosInPath < paths[curSubWorld][currentState[1]]->getVertexCount()-1)
    {
        sf::Vertex nextPos = (* (paths[curSubWorld][currentState[1]]))[curPosInPath+1];
        if(curPos.position.x < nextPos.position.x)
        {
            curPosInPath++;
            return nextPos.position.x - curPos.position.x;
        }
    }

    if (curPosInPath > 0)
    {
        sf::Vertex prevPos = (* (paths[curSubWorld][currentState[1]]))[curPosInPath-1];
        if(curPos.position.x < prevPos.position.x)
        {
            curPosInPath--;
            return prevPos.position.x - curPos.position.x;
        }
    }

    return 0;
}

int Overworld::moveLeft()
{
    sf::Vertex curPos = (* (paths[curSubWorld][currentState[1]]))[curPosInPath];
    if(curPosInPath < paths[curSubWorld][currentState[1]]->getVertexCount()-1)
    {
        sf::Vertex nextPos = (* (paths[curSubWorld][currentState[1]]))[curPosInPath+1];
        if(curPos.position.x > nextPos.position.x)
        {
            curPosInPath++;
            return curPos.position.x - nextPos.position.x;
        }
    }

    if (curPosInPath > 0)
    {
        sf::Vertex prevPos = (* (paths[curSubWorld][currentState[1]]))[curPosInPath-1];
        if(curPos.position.x > prevPos.position.x)
        {
            curPosInPath--;
            return curPos.position.x - prevPos.position.x;
        }
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

int Overworld::whichOverworld()
{
    switch(currentState[1])
    {
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
        std::cerr << "No matching state for the current state." << std::endl;
        return 0;
        break;
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

void Overworld::switchOverworlds()
{
    curPosInPath = 0;
    curSubWorld = curSubWorld == 0 ? 1 : 0;
    currentState[1] = 0;
}

int Overworld::getLevelFromPath()
{
    sf::Vertex curPos = (* (paths[curSubWorld][currentState[1]]))[curPosInPath];
    for (size_t i = 0; i < levelPos[curSubWorld].size(); ++i)
    {
        if(levelPos[curSubWorld][i][0] == curPos.position.x && levelPos[curSubWorld][i][1] == curPos.position.y)
        {
            return i;
        }
    }
    return -1;
}
