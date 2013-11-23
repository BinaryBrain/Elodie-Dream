#ifndef CHARACTERSPRITE_H
#define CHARACTERSPRITE_H

#include "AnimatedSprite.h"

enum class SpriteStance {
    STANDING, WALKING_LEFT, WALKING_RIGHT, JUMPING, ATTACKING
};

class CharacterSprite : public AnimatedSprite {
public:
    CharacterSprite();
    virtual ~CharacterSprite();

    SpriteStance getCurrentStance();
    void setCurrentStance(SpriteStance newStance);
protected:
private:
    SpriteStance currentStance = SpriteStance::STANDING;
};

#endif // CHARACTERSPRITE_H
