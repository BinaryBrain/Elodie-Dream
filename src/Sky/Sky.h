#ifndef SKY_H
#define SKY_H

#include "../Displayable/Displayable.h"

class Sky : public Displayable {
public:
    Sky(GameView* gameView);
    void display();
    virtual ~Sky();
private:
};

#endif // SKY_H
