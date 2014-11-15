#include "Death.h"

const int Death::CHAR_SIZE = 30;
const float Death::INTERSPACE = 50;
const std::string Death::MUSIC = "death.ogg";
const std::string Death::DREAMOVER = "assets/img/sprites/dreamover.png";

Death::Death(GameView& view, bool isMute) : Displayable(view)
{
    float viewX = gameView.getSizeX();
    float viewY = gameView.getSizeY();

    rect.setSize(sf::Vector2f(viewX, viewY));
    rect.setFillColor(sf::Color(0x00, 0x00, 0x00, 0xFF));
    rect.setPosition(0, 0);

    wokeUp.setString("You woke up... ");
    wokeUp.setFont(globalFont);
    wokeUp.setCharacterSize(CHAR_SIZE);

    float midX = viewX/2;
    float midY = viewY/2;

    texture.loadFromFile(DREAMOVER);
    elo.setTexture(texture);

    float midEloX = (elo.getLocalBounds().width)/2;
    float midEloY = (elo.getLocalBounds().height)/2;
    float botElo = midY + midEloY;
    elo.setPosition(midX - midEloX, midY - midEloY);

    wokeUp.setPosition(midX - wokeUp.getLocalBounds().width/2, botElo + INTERSPACE);

    if (!music.openFromFile(MUSIC_PATH + "/" + MUSIC))
    {
        // TODO Handle error
    }
    else
    {
        music.setLoop(true);
        if (!isMute)
        {
            music.play();
        }
    }

    view.addView(ViewLayer::DEATH, this);
}

Death::~Death()
{

}

void Death::display()
{
    gameView.addDrawable(ViewLayer::DEATH, &rect);
    gameView.addDrawable(ViewLayer::DEATH, &elo);
    gameView.addDrawable(ViewLayer::DEATH, &wokeUp);
}

sf::Music& Death::getMusic()
{
    return music;
}
