#ifndef DEATH_H
#define DEATH_H

#include "../Displayable/Displayable.h"
#include "../Game/GameView.h"
#include "../const.h"
#include "../font.h"

#include <SFML/Audio.hpp>

class Death : public Displayable
{
public:
    static const int CHAR_SIZE;
    static const float INTERSPACE;
    static const std::string MUSIC;
    static const std::string DREAMOVER;

public:
    Death(GameView& view, bool isMute);
    virtual ~Death();

    void display();
    sf::Music& getMusic();

private:
    sf::RectangleShape rect;
    sf::Text wokeUp;
    sf::Texture texture;
    sf::Sprite elo;
    sf::Music music;

};

#endif // DEATH_H
