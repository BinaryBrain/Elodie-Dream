#include "Earth.h"

Earth::Earth(GameView* gameView, LevelEnv env, int tilesNumber, sf::Vector2f* cameraPos) : Displayable(gameView) {
    std::string filename;
    this->cameraPos = cameraPos;

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

    earth.setTextureRect(sf::IntRect(0,0, tilesNumber*32 + WINDOW_WIDTH,WINDOW_HEIGHT));
    earth.setTexture(earthTexture);

    gameView->addView(ViewLayer::EARTH, this);
}

Earth::~Earth() {
    //dtor
}

void Earth::display() {
    earth.setPosition(sf::Vector2f(-cameraPos->x/2, 0));
    gameView->addDrawable(ViewLayer::EARTH, &earth);
}
