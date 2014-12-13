#include "Overworld.h"

Overworld::Overworld(GameView& gameView, bool muted) : Displayable(gameView)
{

    std::cout << "Constructing overworld" << std::endl;
    JsonAccessor worldStructureAcccessor;

    worldStructureAcccessor.loadJsonFrom("assets/config/levels/worldStruct.json");

    int subWorldsNumber = worldStructureAcccessor.getInt("subWorldsNumber");

    std::vector<int> envsPerSubworld = worldStructureAcccessor.getIntVector("envsPerSubworld");

    std::vector<int> levelsPerSubworld = worldStructureAcccessor.getIntVector("levelsPerSubworld");

    for (int w = 0; w < subWorldsNumber; ++w)
    {
        std::cout << "Loading new subworld : " << w << std::endl;
        overworldSprites.push_back(std::vector<sf::Sprite>());
        overworldTextures.push_back(std::vector<sf::Texture*>());
        for (int i = 0; i < envsPerSubworld[w]; ++i)
        {
            sf::Texture* overworld = new sf::Texture;
            overworldTextures[w].push_back(overworld);
            overworldTextures[w].back()->loadFromFile("assets/img/overworld/subWorld"+ Utils::itos(w) +"/overworld" + Utils::itos(i) + ".png");
            overworldSprites[w].push_back(sf::Sprite(*(overworldTextures[w].back())));
        }
        std::cout << "Images loaded" << std::endl;
        JsonAccessor accessor;
        accessor.loadJsonFrom("assets/config/levels/subWorld" + Utils::itos(w) + "/pos.json");

        levelPos.push_back(std::vector< std::vector< int > >());
        for (int i = 0; i < levelsPerSubworld[w]; ++i)
        {
            levelPos[w].push_back(accessor.getIntVector(Utils::itos(i)));
        }

        std::cout << "Pos loaded" << std::endl;

        levelSpotSprites.push_back(std::vector<sf::Sprite*>());
        for (int i = 0; i < levelsPerSubworld[w]; ++i)
        {
            sf::Texture* spotTexture = new sf::Texture;
            spotTexture->loadFromFile("assets/img/overworld/spot_level.png");
            sf::Sprite* spotSprite = new sf::Sprite(*spotTexture);
            spotSprite->setPosition((levelPos[w][i])[0] - 16, (levelPos[w][i])[1] - 16);
            levelSpotSprites[w].push_back(spotSprite);
        }

        std::cout << "Spots loaded" << std::endl;

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

        std::cout << "Paths sprites loaded" << std::endl;

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

        std::cout << "Paths loaded" << std::endl;
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

void Overworld::evolve(int minLevel, int maxLevel)
{
    maxLevel = minLevel > maxLevel ? minLevel : maxLevel;
    switch(currentState[1])
    {
    case states::UNIL1:
        currentState[1] = states::UNIL2;
        break;
    case states::UNIL2:
        currentState[1] = states::CASTLE1;
        break;
    case states::CASTLE1:
        currentState[1] = states::CASTLE2;
        break;
    case states::CASTLE2:
        currentState[1] = states::VOLCANO1;
        break;
    case states::VOLCANO1:
        currentState[1] = states::VOLCANO2;
        break;
    case states::VOLCANO2:
        currentState[1] = states::FRELJORD1;
        break;
    case states::FRELJORD1:
        currentState[1] = states::FRELJORD2;
        break;
    default:
        break;
    }

    currentState[1] = (int)currentState[1] > maxLevel ? (states) maxLevel : currentState[1];
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

int Overworld::getLevelToLoad()
{
    if(curPosInPath == 0)
    {
        return 0;
    }
    else if (curPosInPath == 1)
    {
        return 1;
    }
    else if (curPosInPath == 3)
    {
        return 2;
    }
    else if (curPosInPath == 4)
    {
        return 3;
    }
    else if (curPosInPath == 5)
    {
        return 4;
    }
    else if (curPosInPath == 7)
    {
        return 5;
    }
    else if (curPosInPath == 8)
    {
        return 6;
    }
    else if (curPosInPath == 10)
    {
        return 7;
    }
    else
    {
        return -1;
    }
}

const std::vector<int>& Overworld::getState()
{
    return currentState;
}

void Overworld::setState(int state)
{
    this->currentState[1] = static_cast<states>(state);
}

void Overworld::setToLevel(int level)
{
    switch(level)
    {
    case 0:
        curPosInPath = 0;
        break;
    case 1:
        curPosInPath = 1;
        break;
    case 2:
        curPosInPath = 3;
        break;
    case 3:
        curPosInPath = 4;
        break;
    case 4:
        curPosInPath = 5;
        break;
    case 5:
        curPosInPath = 7;
        break;
    case 6:
        curPosInPath = 8;
        break;
    case 7:
        curPosInPath = 10;
        break;
    default:
        curPosInPath = 0;
    }
}

void Overworld::switchOverworlds(){
    curPosInPath = 0;
    curSubWorld = curSubWorld == 0 ? 1 : 0;
    currentState[1] = 0;
}
