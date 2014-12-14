#include "Sky.h"

Sky::Sky(GameView& gameView, LevelEnv env, int tilesNumber, sf::Vector2f& cameraPosArg, float slow) : Displayable(gameView), cameraPos(cameraPosArg)
{
    std::string filename;
    this->slow = slow;

    switch(env)
    {
    case LevelEnv::CASTLE:
        filename = ENVIRONMENT_TEXTURES_PATH + "/" + LEVELENV_CASTLE + "/background.png";
        break;
    case LevelEnv::FRELJORD:
        filename = ENVIRONMENT_TEXTURES_PATH + "/" + LEVELENV_FRELJORD + "/background.png";
        break;
    case LevelEnv::FIELD:
        filename = ENVIRONMENT_TEXTURES_PATH + "/" + LEVELENV_FIELD + "/background.png";
        break;
    case LevelEnv::VOLCANO:
        filename = ENVIRONMENT_TEXTURES_PATH + "/" + LEVELENV_VOLCANO + "/background.png";
        break;
    case LevelEnv::SPACE:
        filename = ENVIRONMENT_TEXTURES_PATH + "/" + LEVELENV_SPACE + "/background.png";
        break;
    case LevelEnv::MODERN:
        filename = ENVIRONMENT_TEXTURES_PATH + "/" + LEVELENV_MODERN + "/background.png";
        break;
    default:
        filename = ENVIRONMENT_TEXTURES_PATH + "/" + LEVELENV_FIELD + "/background.png";
        break;
    }

    skyTexture.loadFromFile(filename);
    skyTexture.setRepeated(true);

    //sky.scale(sf::Vector2f(dimX, 1));
    sky.setTexture(skyTexture);
    sky.setTextureRect(sf::IntRect(0,0, tilesNumber*32*slow + WINDOW_WIDTH+100,WINDOW_HEIGHT));
    gameView.addView(ViewLayer::SKY, this);
}

Sky::~Sky()
{
    //dtor
}

void Sky::display()
{
    sky.setPosition(sf::Vector2f(-cameraPos.x*slow, 0));
    gameView.addDrawable(ViewLayer::SKY, &sky);
}
