#include "Death.h"

Death::Death(GameView * view, bool isMute) : Displayable(view) {
    float viewX(gameView->getWindow()->getSize().x);
    float viewY(gameView->getWindow()->getSize().y);

    rect.setSize(sf::Vector2f(viewX, viewY));
    rect.setFillColor(sf::Color(0x00, 0x00, 0x00, 0xFF));
    rect.setPosition(0, 0);

    wokeUp = new sf::Text("You woke up... ", globalFont);
    wokeUp->setCharacterSize(30);

    float midX = WINDOW_WIDTH/2;
    float midY = WINDOW_HEIGHT/2;

    texture.loadFromFile("assets/img/sprites/dreamover.png");
    elo.setTexture(texture);

    float midEloX = (elo.getLocalBounds().width)/2;
    float midEloY = (elo.getLocalBounds().height)/2;
    float botElo = midY + midEloY;
    elo.setPosition(midX - midEloX, midY - midEloY);

    wokeUp->setPosition(midX - wokeUp->getLocalBounds().width/2, botElo + GAMEOVER_INTERSPACE);


    view->addView(ViewLayer::DEATH, this);

    if (!music.openFromFile(MUSIC_PATH+"/"+DEATH_MUSIC)) {
        // TODO Handle error
    } else {
        music.setLoop(true);

        if(!isMute) {
            music.play();
        }
    }

}

Death::~Death() {
    delete wokeUp;
}

void Death::display() {
    gameView->addDrawable(ViewLayer::DEATH, &rect);
    gameView->addDrawable(ViewLayer::DEATH, &elo);
    gameView->addDrawable(ViewLayer::DEATH, wokeUp);
}
