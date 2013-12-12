#ifndef SKY_H
#define SKY_H

#include <string>

#include "../const.h"
#include "../env.h"
#include "../Game/GameView.h"
#include "../Displayable/Displayable.h"

class Sky : public Displayable {
public:
    Sky(GameView* gameView, LevelEnv env);
    void display();
    virtual ~Sky();
private:
    sf::Sprite sky;
    sf::Texture skyTexture;
};

#endif // SKY_H
