#ifndef DEATH_H
#define DEATH_H

#include "../Displayable/Displayable.h"
#include "../Game/Game.h"
#include "../Game/GameView.h"
#include "../const.h"

#include <SFML/Audio.hpp>

class Death : public Displayable {
public:
    Death(GameView* view, bool isMute);
    virtual ~Death();

    void display();

private:
    sf::RectangleShape rect;
    sf::Font* font;
    sf::Text* oh;
    sf::Text* wokeUp;
    sf::Texture texture;
    sf::Sprite elo;
    sf::Music music;

};

#endif // DEATH_H
