#include "EndingScreen.h"

EndingScreen::EndingScreen(GameView& view, bool isMute, std::string image) : Displayable(view)
{
    texture.loadFromFile(image);
    endingImage.setTexture(texture);
    endingImage.setPosition(0,0);

    view.addView(ViewLayer::ENDINGSCREEN, this);

    muted = isMute;
}

EndingScreen::~EndingScreen()
{
}

void EndingScreen::display()
{
    gameView.addDrawable(ViewLayer::ENDINGSCREEN, &endingImage);
}

sf::Music& EndingScreen::getMusic()
{
    return music;
}

void EndingScreen::playMusic()
{
    if (!music.openFromFile(MUSIC_PATH+"/"+END_MUSIC))
    {
        // TODO Handle error
    }
    else
    {
        music.setLoop(false);

        if(!muted)
        {
            music.play();
        }
    }

}
