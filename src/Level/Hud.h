#ifndef HUD_H
#define HUD_H

#include "../env.h"
#include "../Displayable/Displayable.h"
#include "../Game/GameView.h"

class Hud : public Displayable {
public:
    // Immersion Bar
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
    static const float IMMERSION_BAR_OUTLINE_THICKNESS;
    static const sf::Color IMMERSION_BAR_FILL;
    static const sf::Color IMMERSION_BAR_OUTLINE;

    Hud(GameView* gameView);
    virtual ~Hud();
    void display();
    void setLevel(int level);

private:
    sf::Sprite* bgSprite = NULL;
    sf::Texture* bgTexture = NULL;
    sf::Sprite* barSprite = NULL;
    sf::Texture* barTexture = NULL;
    int level = 100;
    float xRatioBg = 1;
    float yRatioBg = 1;
    float xRatioBar = 1;
    float yRatioBar = 1;
    int barWidth = 0;
    int barHeight = 0;
};

#endif // HUD_H
