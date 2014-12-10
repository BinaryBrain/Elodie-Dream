#ifndef HUD_H
#define HUD_H

#include "../env.h"
#include "../font.h"
#include "../Displayable/Displayable.h"
#include "../Game/GameView.h"

class Hud : public Displayable
{
public:
    static const std::string IMMERSION_BAR_IMG;
    static const std::string IMMERSION_BAR_BG_IMG;
    static const float IMMERSION_BAR_X;
    static const float IMMERSION_BAR_DELTA_X;
    static const float IMMERSION_BAR_Y;
    static const float IMMERSION_BAR_DELTA_Y;
    static const float IMMERSION_BAR_W;
    static const float IMMERSION_BAR_H;
    static const float IMMERSION_BG_W;
    static const float IMMERSION_BG_H;
    static const float IMMERSION_IMAGE_W;
    static const float IMMERSION_IMAGE_H;

    static const int SCORE_CHAR_SIZE;
    static const float SCORE_BG_W;
    static const float SCORE_BG_H;
    static const float SCORE_PADDING;
    static const float SCORE_MARGIN_R;
    static const float SCORE_MARGIN_T;

public:
    Hud(GameView& gameView);
    virtual ~Hud();
    void display();
    void setLevel(int level);
    void setScore(int score);

private:
    sf::Texture barBgTexture;
    sf::Sprite barBgSprite;
    sf::Texture barTexture;
    sf::Sprite barSprite;

    sf::RectangleShape bgScore;
    sf::Text scoreText;

    int level = 100;
    float xRatioBg = 1;
    float yRatioBg = 1;
    float xRatioBar = 1;
    float yRatioBar = 1;
    int barWidth = 0;
    int barHeight = 0;
    int score = 0;
};

#endif // HUD_H
