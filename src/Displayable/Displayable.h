#ifndef DISPLAYABLE_H
#define DISPLAYABLE_H

#include <SFML/Graphics.hpp>

class GameView;

class Displayable
{
    public:
        Displayable();
        virtual ~Displayable();
        virtual void display(GameView* view) = 0;
        sf::View* getView();
    protected:
    private:
        sf::View* view = new sf::View();

};

#endif // DISPLAYABLE_H
