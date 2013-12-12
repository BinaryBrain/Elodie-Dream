#ifndef OVERWORLD_H
#define OVERWORLD_H

#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "../Game/Game.h"
#include "../Entity/Elodie.h"
#include "../Json/JsonAccessor.h"
#include "../Game/GameView.h"
#include "../Displayable/Displayable.h"

class Game;

class Overworld : public Displayable{
public:
    Overworld(GameView* gameView, bool muted);
    virtual ~Overworld();

    Elodie* getElodie();
    int getCurrentEnv();
    int moveUp();
    int moveDown();
    int moveRight();
    int moveLeft();
    void evolve();
    void display();
    void resetPos();
    void playMusic();
    void stopMusic();

    int getLevelToLoad();

    int getState();
    void setState(int state);

    sf::Music* getMusic();

protected:
private:
    enum states {
        UNIL1 = 0,
        UNIL2 = 1,
        CASTLE1 = 2,
        CASTLE2 = 3,
        VOLCANO1 = 4,
        VOLCANO2 = 5,
        FRELJORD1 = 6,
        FRELJORD2 = 7
    };

    states currentState;
    std::vector<sf::Sprite*> overworldSprites;
    std::vector<sf::VertexArray*> paths;
    std::vector<sf::Sprite*> pathSprites;
    std::vector<std::vector<int>*> levelPos;

    size_t curPosInPath=0;

    std::vector<sf::Sprite*> levelSpotSprites;

    Elodie* elodie;
    sf::Music music;

    int whichOverworld();
};

#endif // OVERWORLD_H
