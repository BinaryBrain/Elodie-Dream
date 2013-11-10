#ifndef ELODIESPRITE_H
#define ELODIESPRITE_H
#include <iostream>
#include "CharacterSprite.h"


class ElodieSprite : public CharacterSprite
{
    public:
        ElodieSprite();
        virtual ~ElodieSprite();
        void walk();
        void stand();
    protected:
    private:
        Animation standingAnimation;
        Animation walkingAnimation;
        sf::Texture texture;
};

#endif // ELODIESPRITE_H
