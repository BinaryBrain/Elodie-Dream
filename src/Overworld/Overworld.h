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
    Overworld(GameView* gameView);
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

    sf::Music* getMusic();

protected:
private:
    enum states {
        UNIL = 0,
        CASTLE = 1,
        VOLCANO = 2,
        FRELJORD = 3
    };

    states currentState;
    std::vector<sf::Sprite*> overworldSprites;
    std::vector<sf::VertexArray*> paths;
    std::vector<std::vector<int>*> levelPos;

    size_t curPosInPath=0;

    Elodie* elodie;
    sf::Music music;
};

#endif // OVERWORLD_H
