#ifndef EARTH_H
#define EARTH_H

#include <string>

#include "../const.h"
#include "../env.h"
#include "../Game/GameView.h"
#include "../Displayable/Displayable.h"

class Earth : public Displayable {
public:
    Earth(GameView* gameView, LevelEnv env);
    void display();
    virtual ~Earth();
private:
    sf::Sprite earth;
    sf::Texture earthTexture;
};

#endif // EARTH_H
