#include "Earth.h"

Earth::Earth(GameView* gameView, LevelEnv env) : Displayable(gameView) {
    std::string filename;

    switch(env) {
    case LevelEnv::CASTLE:
        filename = ENVIRONMENT_TEXTURES_PATH + "/" + LEVELENV_CASTLE + "/backlayer.png";
        break;
    case LevelEnv::FREJLORD:
        filename = ENVIRONMENT_TEXTURES_PATH + "/" + LEVELENV_FRELJORD + "/background.png";
        break;
    case LevelEnv::FIELD:
        filename = ENVIRONMENT_TEXTURES_PATH + "/" + LEVELENV_FIELD + "/backlayer.png";
        break;
    case LevelEnv::VOLCANO:
        filename = ENVIRONMENT_TEXTURES_PATH + "/" + LEVELENV_VOLCANO + "/backlayer.png";
        break;
    default:
        filename = ENVIRONMENT_TEXTURES_PATH + "/" + LEVELENV_FIELD + "/backlayer.png";
        break;
    }

    earthTexture.loadFromFile(filename);
    earthTexture.setRepeated(true);

    float viewX(gameView->getWindow()->getSize().x);

    float dimX(viewX);

    earth.scale(sf::Vector2f(dimX, 1));
    earth.setTexture(earthTexture);

    gameView->addView(ViewLayer::EARTH, this);
}

Earth::~Earth() {
    //dtor
}

void Earth::display() {

    gameView->addDrawable(ViewLayer::EARTH, &earth);
}
