#ifndef HUD_H
#define HUD_H

#include "../const.h"
#include "../env.h"
#include "../Displayable/Displayable.h"
#include "../Game/GameView.h"

class Hud : public Displayable {
public:
    Hud(GameView* view);
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
