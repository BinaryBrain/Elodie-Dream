#ifndef TITLESCREEN_H
#define TITLESCREEN_H

#include "../Displayable/Displayable.h"
#include "../Game/GameView.h"

class TitleScreen : public Displayable
{
public:
    static const std::string TITLE_TEXT;
    static const std::string ANIMATED_BACKGROUND_PATH;

    TitleScreen(GameView& gameView);
    virtual ~TitleScreen();
    void display();

private:
    bool MENU_PORO_IS_LOADED = false;
    sf::Texture titleTextTexture;
    sf::Sprite titleText;
    sf::Texture tbgTexture;
    sf::Sprite tbg;
    std::map< int, sf::Texture* > poroTextures;
    int poroIndex;
};

#endif // TITLESCREEN_H
