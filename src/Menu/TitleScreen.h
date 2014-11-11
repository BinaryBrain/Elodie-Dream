#ifndef TITLESCREEN_H
#define TITLESCREEN_H

#include "../Displayable/Displayable.h"
#include "../Game/GameView.h"

class TitleScreen : public Displayable {
public:
    TitleScreen(GameView& gameView);
    virtual ~TitleScreen();
    void display();
protected:
private:
    sf::Texture titleTextTexture;
    sf::Sprite titleText;
    sf::Texture tbgTexture;
    sf::Sprite tbg;
    std::map< int, sf::Texture* > poroTextures;
    int poroIndex;
};

#endif // TITLESCREEN_H
