#ifndef BRISTLESPRITE_H_INCLUDED
#define BRISTLESPRITE_H_INCLUDED

#include <iostream>
#include <string>
#include <map>

#include "../../const.h"
#include "../../env.h"
#include "../EnemySprite.h"
#include "../../Include/EntityInfo.h"


class BristleSprite : public EnemySprite {
public:
    BristleSprite(EntityInfo *informations);
    virtual ~BristleSprite();
    void changeStance(std::string stance, sf::Time speed);
protected:
private:
    std::map< std::string, Animation > animations;
    sf::Texture texture;
};

#endif // BRISTLESPRITE_H_INCLUDED
