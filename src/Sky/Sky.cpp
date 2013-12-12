#include "Sky.h"

Sky::Sky(GameView* gameView, LevelEnv env) : Displayable(gameView) {
    std::string filename;

    switch(env) {
    case LevelEnv::CASTLE:
        filename = ENVIRONMENT_TEXTURES_PATH + "/" + LEVELENV_CASTLE + "/background.png";
        break;
    case LevelEnv::FREJLORD:
        filename = ENVIRONMENT_TEXTURES_PATH + "/" + LEVELENV_FRELJORD + "/background.png";
        break;
    case LevelEnv::FIELD:
        filename = ENVIRONMENT_TEXTURES_PATH + "/" + LEVELENV_FIELD + "/background.png";
        break;
    case LevelEnv::VOLCANO:
        filename = ENVIRONMENT_TEXTURES_PATH + "/" + LEVELENV_VOLCANO + "/background.png";
        break;
    default:
        filename = ENVIRONMENT_TEXTURES_PATH + "/" + LEVELENV_FIELD + "/background.png";
        break;
    }

    skyTexture.loadFromFile(filename);
    skyTexture.setRepeated(true);

    float viewX(gameView->getWindow()->getSize().x);

    float dimX(viewX);

    //sky.scale(sf::Vector2f(dimX, 1));
    sky.setTexture(skyTexture);

    gameView->addView(ViewLayer::SKY, this);
}

Sky::~Sky() {
    //dtor
}

void Sky::display() {

    gameView->addDrawable(ViewLayer::SKY, &sky);
}
