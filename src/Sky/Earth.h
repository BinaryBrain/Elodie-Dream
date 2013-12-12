#ifndef EARTH_H
#define EARTH_H

#include <string>

#include "../const.h"
#include "../env.h"
#include "../Game/GameView.h"
#include "../Displayable/Displayable.h"

class Earth : public Displayable {
public:
    Earth(GameView* gameView, LevelEnv env, int tilesNumber, sf::Vector2f*);
    void display();
    virtual ~Earth();
private:
    sf::Sprite earth;
    sf::Texture earthTexture;
    sf::Vector2f* cameraPos;
};

#endif // EARTH_H
