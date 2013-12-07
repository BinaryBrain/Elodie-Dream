#ifndef SHEEPSPRITE_H_INCLUDED
#define SHEEPSPRITE_H_INCLUDED

#include <iostream>
#include <string>
#include <map>

#include "../../const.h"
#include "../../env.h"
#include "../EnemySprite.h"
#include "../../Include/EntityInfo.h"


class SheepSprite : public EnemySprite {
public:
    SheepSprite(EntityInfo *informations);
    virtual ~SheepSprite();
    void changeStance(std::string stance, sf::Time speed);
protected:
private:
    std::map< std::string, Animation > animations;
    sf::Texture texture;
};

#endif // SHEEPSPRITE_H_INCLUDED
