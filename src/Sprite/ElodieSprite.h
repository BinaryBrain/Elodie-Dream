#ifndef ELODIESPRITE_H
#define ELODIESPRITE_H

#include <iostream>
#include <string>
#include <map>

#include "../const.h"
#include "../env.h"
#include "CharacterSprite.h"
#include "../Include/EntityInfo.h"


class ElodieSprite : public CharacterSprite
{
public:
    ElodieSprite(EntityInfo *informations);
    virtual ~ElodieSprite();
    void changeStance(std::string stance, sf::Time speed);
    void walk();
    void stand();
protected:
private:
    std::map< std::string, Animation > animations;
    sf::Texture texture;
};

#endif // ELODIESPRITE_H
