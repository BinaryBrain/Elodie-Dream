#ifndef ELODIE_H
#define ELODIE_H

#include "Entities.h"
#include "../Sprite/ElodieSprite.h"


class Elodie : public Entities
{
    public:
        Elodie();
        Elodie(sf::Vector2f position);
        Elodie(float x, float y);
        ElodieSprite* getSprite();
        sf::Vector2f* getPosition();
        void walk();
        void stand();
        virtual ~Elodie();

    protected:

    private:
        void init();

        ElodieSprite *sprite;

        int centerX = 21;
        int centerY = 32;
};

#endif // ELODIE_H
