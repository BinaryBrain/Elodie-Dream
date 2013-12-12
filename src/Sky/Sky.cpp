#include "Sky.h"

Sky::Sky(GameView* gameView, LevelEnv env, int tilesNumber, sf::Vector2f* cameraPos, float slow) : Displayable(gameView) {
    std::string filename;
    this->cameraPos = cameraPos;
    this->slow = slow;

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
    sky.setTextureRect(sf::IntRect(0,0, tilesNumber*32 + WINDOW_WIDTH,WINDOW_HEIGHT));
    gameView->addView(ViewLayer::SKY, this);
}

Sky::~Sky() {
    //dtor
}

void Sky::display() {
    sky.setPosition(sf::Vector2f(-cameraPos->x*slow, 0));
    gameView->addDrawable(ViewLayer::SKY, &sky);
}
