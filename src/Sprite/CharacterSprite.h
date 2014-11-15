#ifndef CHARACTERSPRITE_H
#define CHARACTERSPRITE_H

#include <string>
#include "AnimatedSprite.h"

class CharacterSprite : public AnimatedSprite
{
public:
    CharacterSprite();
    virtual ~CharacterSprite();

    std::string getCurrentStance();
    void setCurrentStance(std::string newStance);
protected:
private:
    std::string currentStance = "";
};

#endif // CHARACTERSPRITE_H
