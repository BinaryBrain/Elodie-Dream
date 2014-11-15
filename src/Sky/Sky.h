#ifndef SKY_H
#define SKY_H

#include <string>

#include "../const.h"
#include "../env.h"
#include "../Game/GameView.h"
#include "../Displayable/Displayable.h"

class Sky : public Displayable
{
public:
    Sky(GameView& gameView, LevelEnv env, int tilesNumber, sf::Vector2f& cameraPosArg, float slow);
    void display();
    virtual ~Sky();
private:
    sf::Sprite sky;
    sf::Texture skyTexture;
    sf::Vector2f& cameraPos;
    float slow;
};

#endif // SKY_H
