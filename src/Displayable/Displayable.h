#ifndef DISPLAYABLE_H
#define DISPLAYABLE_H

#include <SFML/Graphics.hpp>

class GameView;

class Displayable
{
public:
    Displayable(GameView& g);
    virtual ~Displayable();
    virtual void display() = 0;
    sf::View& getView();

protected:
    GameView& gameView;

private:
    sf::View view;
};

#endif // DISPLAYABLE_H
