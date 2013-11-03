#ifndef ELODIE_H
#define ELODIE_H

#include "Entities.h"
#include "../Sprite/ElodieSprite.h"


class Elodie : public Entities
{
    public:
        Elodie();
        Elodie(sf::Vector2f position);
        virtual ~Elodie();

    protected:

    private:
        void init();

        ElodieSprite *sprite;
};

#endif // ELODIE_H
