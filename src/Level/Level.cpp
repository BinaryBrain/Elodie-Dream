#include "Level.h"
#include "../Json/JsonAccessor.h"

Level::Level(GameView& gameView, std::vector<int> levelNbr, LevelEnv env, Elodie& elodie) :
    Displayable(gameView),
    environement(env)
{
    loadLevel("assets/levels/subWorld" + Utils::itos(levelNbr[0]) + "/level" + Utils::itos(levelNbr[1]) + ".txt", elodie);
    JsonAccessor accessor;

    accessor.loadJsonFrom("assets/levels/subWorld" + Utils::itos(levelNbr[0]) + "/level" + Utils::itos(levelNbr[1]) + ".json");

    int gravity = accessor.getInt("gravity");
    int jumpSpeed = accessor.getInt("jumpSpeed");
    int moveSpeed = accessor.getInt("moveSpeed");
    float zoom = accessor.getDouble("zoom");
    float interRecoveryTime = accessor.getDouble("interRecoveryTime");
    float attackCD = accessor.getDouble("attackCD");
    if (accessor.canTakeElementFrom("ending"))
    {
        std::string endingPath = "assets/img/sprites/menu/" + accessor.getString("ending");
        endingScreen = new EndingScreen(gameView, Game::getInstance().isMute(), endingPath);
    }

    std::string musicPath = "NONE";

    if (accessor.canTakeElementFrom("music"))
    {
        musicPath = accessor.getString("music");
    }


    HORIZONTAL_DISPLAY_MARGIN = WINDOW_WIDTH/(2*zoom) + 2*BLOCK_SIZE;
    VERTICAL_DISPLAY_MARGIN = WINDOW_HEIGHT/(2*zoom) + 12*BLOCK_SIZE;

    elodie.setGravity(gravity);
    elodie.setJumpSpeed(jumpSpeed);
    elodie.setMoveSpeed(moveSpeed);
    elodie.setInterRecoveryTime(interRecoveryTime);
    elodie.setAttackCD(attackCD);

    std::pair< float, float > slow = getSlowVariables(env);
    this->sky = new Sky(gameView, env, tiles[0].size(), elodie.getCameraPosRef(), slow.first);
    this->earth = new Earth(gameView, env, tiles[0].size(), elodie.getCameraPosRef(), slow.second);

    gameView.addView(ViewLayer::LEVEL, this);
    gameView.setZoom(ViewLayer::LEVEL, zoom);

    gameView.setCameraCenter(ViewLayer::LEVEL, elodie.getPosition());

    musicPath = musicPath == "NONE" ? LEVEL_MUSIC : musicPath;
    if (!music.openFromFile(MUSIC_PATH+"/"+musicPath))
    {
        // TODO Handle error
    }
    else
    {
        music.setLoop(true);

        if(!Game::getInstance().isMute())
        {
            music.play();
        }
    }

}

Level::~Level()
{
    for(size_t i(0); i < tiles.size(); ++i)
    {
        for(size_t j(0); j < tiles[i].size(); ++j)
        {
            delete tiles[i][j];
        }
    }

    for(EntityMap::iterator it = entities.begin(); it != entities.end(); ++it)
    {
        if(it->first.compare("elodie"))
        {
            delete it->second;
        }
    }
    delete this->sky;
    delete this->earth;
    if (endingScreen)
    {
        delete endingScreen;
        endingScreen = nullptr;
    }
}

void Level::setEnvironement(LevelEnv env)
{
    this->environement = env;
}

// Load a level from the file system
void Level::loadLevel(std::string filename, Elodie& elodie)
{
    std::string levelSource = FileHandler::getContent(filename);

    Mapper::parse(levelSource, tiles, entities, elodie);
    Mapper::beautify(tiles);

    applyEnv(tiles);
}

// Ask the given view to draw a Level frame
void Level::display()
{
    int cameraCenterX = this->getView().getCenter().x;
    int cameraCenterY = this->getView().getCenter().y;

    int marginLeft = cameraCenterX - HORIZONTAL_DISPLAY_MARGIN;
    int marginRight = cameraCenterX + HORIZONTAL_DISPLAY_MARGIN;
    int startX = marginLeft / 32;
    if (startX < 0 )
    {
        startX = 0;
    }
    size_t endX = marginRight / 32;

    int marginTop = cameraCenterY - VERTICAL_DISPLAY_MARGIN;
    int marginBot = cameraCenterY + VERTICAL_DISPLAY_MARGIN;
    int startY = marginTop / 32;
    if (startY < 0)
    {
        startY = 0;
    }
    size_t endY = marginBot / 32;
    endY = endY > tiles.size() ? tiles.size() : endY;
    for (size_t y=startY; y < endY; y++)
    {
        size_t tmpEndX = endX > tiles[y].size() ? tiles[y].size() : endX;
        for (size_t x=startX; x < tmpEndX; x++)
        {
            if (tiles[y][x])
            {
                tiles[y][x]->setPosition(x*32, y*32);
                gameView.addDrawable(ViewLayer::LEVEL, tiles[y][x]);
            }
        }
    }

    Portal* portal = dynamic_cast<Portal*>(entities["portal"]);
    if (portal->getSprite())
    {
        gameView.addDrawable(ViewLayer::LEVEL, portal->getSprite());
    }
    for(EntityMap::iterator entity_ptr = entities.begin(); entity_ptr != entities.end(); ++entity_ptr)
    {
        if(entity_ptr->first != "elodie" && entity_ptr->first != "portal")
        {
            Entity* entity = entity_ptr->second;
            sf::Sprite* sprite = entity->getSprite();
            if (sprite->getPosition().x > marginLeft
                    && sprite->getPosition().x < marginRight
                    && sprite->getPosition().y < marginBot
                    && sprite->getPosition().y > marginTop)
            {
                if(sprite)
                {
                    gameView.addDrawable(ViewLayer::LEVEL, sprite);
                }
            }
        }
    }
    Elodie* elodie = dynamic_cast<Elodie*>(entities["elodie"]);
    if (elodie->getSprite())
    {
        gameView.addDrawable(ViewLayer::LEVEL, elodie->getSprite());
    }
    gameView.followPoint(ViewLayer::LEVEL, elodie->getCameraPos());
}

void Level::live(const EventHandler& event, sf::Time animate)
{
    std::vector< std::string > toDelete;
    sf::FloatRect scope(0, 0, LIVE_SCOPE, LIVE_SCOPE);
    scope.top = ((Elodie*)entities["elodie"])->getPosition().y - LIVE_SCOPE / 2;
    scope.left = ((Elodie*)entities["elodie"])->getPosition().x - LIVE_SCOPE / 2;
    entities["elodie"]->doStuff(event, tiles, entities, animate);
    for (EntityMap::iterator it = entities.begin(); it != entities.end(); ++it)
    {
        if (it->first != "elodie" && scope.intersects(it->second->returnCurrentHitbox().getArea()))
        {
            it->second->doStuff(event, tiles, entities, animate);
            if (!it->second->isAlive())
            {
                toDelete.push_back(it->first);
            }
        }
    }
    for (size_t i = 0; i < toDelete.size(); ++i)
    {
        delete entities[toDelete[i]];
        entities.erase(toDelete[i]);
    }
}

EntityMap Level::getEntities()
{
    EntityMap entitiesCpy;

    for (EntityMap::iterator it = entities.begin(); it != entities.end(); ++it)
    {
        entitiesCpy.insert(std::make_pair(it->first, it->second));
    }
    return entitiesCpy;
}

void Level::applyEnv(TileMap tiles)
{
    for (size_t y = 0; y < tiles.size(); y++)
    {
        for (size_t x = 0; x < tiles[y].size(); x++)
        {
            if (tiles[y][x])
            {
                sf::Texture* texture = manager.getTileTexture(environement, tiles[y][x]->getType());
                tiles[y][x]->setTexture(*texture);
            }
        }
    }
}

void Level::pause()
{
    entities["elodie"]->pause();
}

void Level::play(sf::Clock *frameClock)
{
    entities["elodie"]->play();
    frameClock->restart();
}

sf::Music& Level::getMusic()
{
    return music;
}

bool Level::isDead()
{
    Elodie* elodie = dynamic_cast<Elodie*>(entities["elodie"]);
    bool outOfCam = gameView.isPointOutsideView(ViewLayer::LEVEL, elodie->getPosition().x, elodie->getPosition().y);
    bool noMoreImmersion = elodie->getImmersionLevel() <= 0;
    bool fellInTheDepths = elodie->getPosition().y > tiles.size()*32;
    return outOfCam || noMoreImmersion || fellInTheDepths;
}

bool Level::isCleared()
{
    Elodie* elodie = dynamic_cast<Elodie*>(entities["elodie"]);
    Portal* portal = dynamic_cast<Portal*>(entities["portal"]);

    return portal->returnCurrentHitbox().getArea().intersects(elodie->returnCurrentHitbox().getArea());
}

bool Level::mustLeave()
{
    return isDead() || isCleared();
}

std::pair <float,float> Level::getSlowVariables(LevelEnv env)
{
    float skyS=0;
    float earthS=0;
    switch(env)
    {
    case LevelEnv::FIELD:
        skyS = 0;
        earthS = 0.5;
        break;
    case LevelEnv::CASTLE:
        skyS = 1.0;
        earthS = 0.4;
        break;
    case LevelEnv::VOLCANO:
        skyS = 0.15;
        earthS = 0.5;
        break;
    case LevelEnv::FRELJORD:
        skyS = 0.2;
        earthS = 2.8;
        break;
    case LevelEnv::SPACE:
        skyS = 0;
        earthS = 0.2;
        break;
    case LevelEnv::MODERN:
        skyS = 0.2;
        earthS = 1;
        break;
    default:
        skyS = 0;
        earthS = 0;
        break;
    }
    return std::make_pair(skyS,earthS);
}

EndingScreen* Level::getEndingScreen()
{
    return endingScreen;
}
