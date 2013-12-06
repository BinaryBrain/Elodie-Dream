#ifndef IMMERSIONBAR_H
#define IMMERSIONBAR_H

#include "../const.h"
#include "../env.h"
#include "../Displayable/Displayable.h"
#include "../Game/GameView.h"

class ImmersionBar : public Displayable {
public:
    ImmersionBar();
    virtual ~ImmersionBar();
    void display(GameView* view);
    void setLevel(int level);
protected:
private:
    sf::RectangleShape outLine;
    sf::RectangleShape filling;
    int level = 100;
};

#endif // IMMERSIONBAR_H
