#ifndef MAGMACUBESPRITE_H_INCLUDED
#define MAGMACUBESPRITE_H_INCLUDED

#include <iostream>
#include <string>
#include <map>

#include "../../const.h"
#include "../../env.h"
#include "../EnemySprite.h"
#include "../../Include/EntityInfo.h"


class MagmaCubeSprite : public EnemySprite {
public:
    MagmaCubeSprite(EntityInfo *informations);
    virtual ~MagmaCubeSprite();
    void changeStance(std::string stance, sf::Time speed);
protected:
private:
    std::map< std::string, Animation > animations;
    sf::Texture texture;
};

#endif // MAGMACUBESPRITE_H_INCLUDED
