#include "Earth.h"

Earth::Earth(GameView& gameView, LevelEnv env, int tilesNumber, sf::Vector2f& cameraPosArg, float slow) : Displayable(gameView), cameraPos(cameraPosArg)
{
    std::string filename;
    this->slow = slow;

    switch(env)
    {
    case LevelEnv::CASTLE:
        filename = ENVIRONMENT_TEXTURES_PATH + "/" + LEVELENV_CASTLE + "/backlayer.png";
        break;
    case LevelEnv::FRELJORD:
        filename = ENVIRONMENT_TEXTURES_PATH + "/" + LEVELENV_FRELJORD + "/backlayer.png";
        break;
    case LevelEnv::FIELD:
        filename = ENVIRONMENT_TEXTURES_PATH + "/" + LEVELENV_FIELD + "/backlayer.png";
        break;
    case LevelEnv::VOLCANO:
        filename = ENVIRONMENT_TEXTURES_PATH + "/" + LEVELENV_VOLCANO + "/backlayer.png";
        break;
    case LevelEnv::SPACE:
        filename = ENVIRONMENT_TEXTURES_PATH + "/" + LEVELENV_SPACE + "/backlayer.png";
        break;
    case LevelEnv::MODERN:
        filename = ENVIRONMENT_TEXTURES_PATH + "/" + LEVELENV_MODERN + "/backlayer.png";
        break;
    default:
        filename = ENVIRONMENT_TEXTURES_PATH + "/" + LEVELENV_FIELD + "/backlayer.png";
        break;
    }

    earthTexture.loadFromFile(filename);
    earthTexture.setRepeated(true);

    earth.setTextureRect(sf::IntRect(0,0, tilesNumber*32*slow + WINDOW_WIDTH+100,WINDOW_HEIGHT));
    earth.setTexture(earthTexture);

    gameView.addView(ViewLayer::EARTH, this);
}

Earth::~Earth()
{
    //dtor
}

void Earth::display()
{
    earth.setPosition(sf::Vector2f(-cameraPos.x*slow, 0));
    gameView.addDrawable(ViewLayer::EARTH, &earth);
}
