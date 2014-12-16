#ifndef ENDINGSCREEN_H
#define ENDINGSCREEN_H

#include "../const.h"
#include "../env.h"
#include "../Displayable/Displayable.h"
#include "../Game/GameView.h"

#include <SFML/Audio.hpp>

class EndingScreen : public Displayable
{
public:
    EndingScreen(GameView& view, bool isMute, std::string image);
    virtual ~EndingScreen();

    void display();
    sf::Music& getMusic();
    void playMusic();

private:
    sf::Texture texture;
    sf::Sprite endingImage;
    sf::Music music;
    bool muted = false;
};

#endif // DEATH_H
