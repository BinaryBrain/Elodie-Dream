#ifndef GHOSTSPRITE_H_INCLUDED
#define GHOSTSPRITE_H_INCLUDED

#include <iostream>
#include <string>
#include <map>

#include "../../const.h"
#include "../../env.h"
#include "../EnemySprite.h"
#include "../../Include/EntityInfo.h"


class GhostSprite : public EnemySprite {
public:
    GhostSprite(EntityInfo *informations);
    virtual ~GhostSprite();
    void changeStance(std::string stance, sf::Time speed);
protected:
private:
    std::map< std::string, Animation > animations;
    sf::Texture texture;
};

#endif // GHOSTSPRITE_H_INCLUDED
