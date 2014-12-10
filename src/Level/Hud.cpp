#include "../Utils/Utils.h"
#include "Hud.h"

const std::string Hud::IMMERSION_BAR_IMG = "assets/img/immersion/immersion_bar.png";
const std::string Hud::IMMERSION_BAR_BG_IMG = "assets/img/immersion/immersion_bar_bg.png";

const float Hud::IMMERSION_BAR_X = 540;
const float Hud::IMMERSION_BAR_DELTA_X = 2;
const float Hud::IMMERSION_BAR_Y = 50;
const float Hud::IMMERSION_BAR_DELTA_Y = 1;
const float Hud::IMMERSION_BAR_W = 204;
const float Hud::IMMERSION_BAR_H = 19;
const float Hud::IMMERSION_BG_W = 202;
const float Hud::IMMERSION_BG_H = 18;
const float Hud::IMMERSION_IMAGE_W = 406;
const float Hud::IMMERSION_IMAGE_H = 38;

const int Hud::SCORE_CHAR_SIZE = 20;
const float Hud::SCORE_BG_W = 120;
const float Hud::SCORE_BG_H = 40;
const float Hud::SCORE_PADDING = 10;
const float Hud::SCORE_MARGIN_R = 50;
const float Hud::SCORE_MARGIN_T = 50;


Hud::Hud(GameView& gameView) : Displayable(gameView)
{
    float viewX = gameView.getSizeX();

    xRatioBg = IMMERSION_BG_W/IMMERSION_IMAGE_W;
    yRatioBg = IMMERSION_BG_H/IMMERSION_IMAGE_H;
    xRatioBar = IMMERSION_BAR_W/IMMERSION_IMAGE_W;
    yRatioBar = IMMERSION_BAR_H/IMMERSION_IMAGE_H;

    barBgTexture.loadFromFile(IMMERSION_BAR_BG_IMG);
    barTexture.loadFromFile(IMMERSION_BAR_IMG);

    barBgSprite.setTexture(barBgTexture);
    barBgSprite.setPosition(IMMERSION_BAR_X, IMMERSION_BAR_Y);
    barBgSprite.setScale(xRatioBg, yRatioBg);

    barSprite.setTexture(barTexture);
    barSprite.setPosition(IMMERSION_BAR_X+IMMERSION_BAR_DELTA_X-1, IMMERSION_BAR_Y+IMMERSION_BAR_DELTA_Y);
    barSprite.setScale(xRatioBar, yRatioBar);

    barWidth = barSprite.getTextureRect().width;
    barHeight = barSprite.getTextureRect().height;

    bgScore.setSize(sf::Vector2f(SCORE_BG_W, SCORE_BG_H));
    bgScore.setFillColor(sf::Color(0x00, 0x00, 0x00, 0xE0));
    bgScore.setPosition(sf::Vector2f(viewX-SCORE_MARGIN_R-SCORE_BG_W, SCORE_MARGIN_T));

    scoreText.setFont(globalFont);
    scoreText.setCharacterSize(SCORE_CHAR_SIZE);
    scoreText.setString("Score");
    scoreText.setPosition(viewX-SCORE_MARGIN_R-SCORE_BG_W+SCORE_PADDING, SCORE_MARGIN_T+SCORE_PADDING);

    gameView.addView(ViewLayer::HUD, this);
}

Hud::~Hud()
{

}

void Hud::display()
{
    barSprite.setTextureRect(sf::IntRect(0,0,barWidth*level/100,barHeight));
    scoreText.setString(Utils::itos(score));

    gameView.addDrawable(ViewLayer::HUD, &barBgSprite);
    gameView.addDrawable(ViewLayer::HUD, &barSprite);
    gameView.addDrawable(ViewLayer::HUD, &bgScore);
    gameView.addDrawable(ViewLayer::HUD, &scoreText);
}

void Hud::setLevel(int level)
{
    this->level = level;
}

void Hud::setScore(int score)
{
    this->score = score;
}
