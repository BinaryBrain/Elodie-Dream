#ifndef DEATH_H
#define DEATH_H

#include "../Displayable/Displayable.h"
#include "../Game/GameView.h"
#include "../const.h"


class Death : public Displayable {
public:
    Death(GameView* view);
    virtual ~Death();

    void display();

private:
    sf::RectangleShape rect;
    sf::Font* font;
    sf::Text* text;
};

#endif // DEATH_H
