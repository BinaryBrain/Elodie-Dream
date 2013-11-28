#ifndef DISPLAYABLE_H
#define DISPLAYABLE_H

#include "../Game/GameView.h"


class Displayable
{
    public:
        Displayable();
        virtual ~Displayable();
        virtual void draw(GameView* view) = 0;
    protected:
    private:
};

#endif // DISPLAYABLE_H
