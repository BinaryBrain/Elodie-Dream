#ifndef GAMECONTENT_H
#define GAMECONTENT_H

#include "../env.h"
#include "../FileHandler/SaveHandler.h"
#include "../Entity/Elodie.h"

/**
* The class handling the game content: gather the content, saves and loads .
*/
class GameContent {
public:
    GameContent();
    virtual ~GameContent();

    void save();
    Elodie* getElodie();
    void setElodie(Elodie* elodie);

private:
    Elodie* elodie = new Elodie();
};

#endif // GAMECONTENT_H
