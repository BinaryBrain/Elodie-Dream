#ifndef IMMERSIONBAR_H
#define IMMERSIONBAR_H

#include "../const.h"
#include "../env.h"
#include "../Displayable/Displayable.h"
#include "../Game/GameView.h"

class ImmersionBar : public Displayable {
public:
    ImmersionBar(GameView* view);
    virtual ~ImmersionBar();
    void display();
    void setLevel(int level);
protected:
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

#endif // IMMERSIONBAR_H
