#include "EndingScreen.h"

EndingScreen::EndingScreen(GameView& view, bool isMute, std::string image) : Displayable(view)
{
    texture.loadFromFile(image);
    endingImage.setTexture(texture);
    endingImage.setPosition(0,0);

    view.addView(ViewLayer::ENDINGSCREEN, this);

    if (!music.openFromFile(MUSIC_PATH+"/"+END_MUSIC))
    {
        // TODO Handle error
    }
    else
    {
        music.setLoop(false);

        if(!isMute)
        {
            music.play();
        }
    }

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
