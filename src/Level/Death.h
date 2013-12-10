#ifndef DEATH_H
#define DEATH_H

#include "../Displayable/Displayable.h"
#include "../Game/GameView.h"


class Death : public Displayable
{
    public:
        Death(GameView* view);
        virtual ~Death();

        void display();
    protected:
    private:
        sf::RectangleShape rect;
};

#endif // DEATH_H
