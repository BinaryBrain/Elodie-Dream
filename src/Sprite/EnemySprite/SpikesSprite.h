#ifndef SPIKESSPRITE_H_INCLUDED
#define SPIKESSPRITE_H_INCLUDED

#include <iostream>
#include <string>
#include <map>

#include "../../const.h"
#include "../../env.h"
#include "../EnemySprite.h"
#include "../../Include/EntityInfo.h"


class SpikesSprite : public EnemySprite {
public:
    SpikesSprite(EntityInfo *informations);
    virtual ~SpikesSprite();
    void changeStance(std::string stance, sf::Time speed);
protected:
private:
    std::map< std::string, Animation > animations;
    sf::Texture texture;
};

#endif // SPIKESSPRITE_H_INCLUDED
