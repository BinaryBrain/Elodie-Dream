#ifndef GIRLY_H
#define GIRLY_H

#include <SFML/Graphics.hpp>

#include "../env.h"
#include "../Game/GameView.h"
#include "../Displayable/Displayable.h"

class Girly: public Displayable {
public:
    Girly();
    virtual ~Girly();

    void display(GameView* view);

private:
    sf::RectangleShape filter;
};

#endif // GIRLY_H
