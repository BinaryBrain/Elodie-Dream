#include "Hud.h"

Hud::Hud(GameView* gameView) : Displayable(gameView) {
    xRatioBg = IMMERSION_BG_W/IMMERSION_IMAGE_W;
    yRatioBg = IMMERSION_BG_H/IMMERSION_IMAGE_H;
    xRatioBar = (IMMERSION_BAR_W)/IMMERSION_IMAGE_W;
    yRatioBar = (IMMERSION_BAR_H)/IMMERSION_IMAGE_H;
    bgTexture = new sf::Texture;
    bgTexture->loadFromFile("assets/img/immersion/immersion_bar_bg.png");
    bgSprite = new sf::Sprite(*bgTexture);
    bgSprite->setPosition(IMMERSION_BAR_X, IMMERSION_BAR_Y);
    bgSprite->setScale(xRatioBg, yRatioBg);
    barTexture = new sf::Texture;
    barTexture->loadFromFile("assets/img/immersion/immersion_bar.png");
    barSprite = new sf::Sprite(*barTexture);
    barSprite->setPosition(IMMERSION_BAR_X+IMMERSION_BAR_DELTA_X-1, IMMERSION_BAR_Y+IMMERSION_BAR_DELTA_Y);
    barSprite->setScale(xRatioBar, yRatioBar);
    barWidth = barSprite->getTextureRect().width;
    barHeight = barSprite->getTextureRect().height;
}

Hud::~Hud() {
    if (bgSprite) {
        delete bgSprite;
        bgSprite = NULL;
    }

    if (bgTexture) {
        delete bgTexture;
        bgTexture = NULL;
    }

    if (barSprite) {
        delete barSprite;
        barSprite = NULL;
    }

    if (barTexture) {
        delete barTexture;
        barTexture = NULL;
    }
}

void Hud::display() {
    barSprite->setTextureRect(sf::IntRect(0,0,barWidth*level/100,barHeight));
    gameView->addDrawable(ViewLayer::HUD, bgSprite);
    gameView->addDrawable(ViewLayer::HUD, barSprite);
}

void Hud::setLevel(int level) {
    this->level = level;
}
