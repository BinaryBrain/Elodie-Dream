#include "../Utils/Utils.h"
#include "TitleScreen.h"

bool MENU_PORO_IS_LOADED = false; // TODO global variable lol

TitleScreen::TitleScreen(GameView& gameView) : Displayable(gameView)
{
    // Background
    if(!MENU_PORO_IS_LOADED)
    {
        poroIndex = MENU_BACKGROUND_FIRST_FRAME;
        for(int i = MENU_BACKGROUND_FIRST_FRAME; i <= MENU_BACKGROUND_LAST_FRAME; i++)
        {
            sf::Texture* poroTexture = new sf::Texture();
            if(!poroTexture->loadFromFile(MENU_ANIMATED_BACKGROUND_PATH+"/"+Utils::toStringWithLength(i, 4)+".png"))
                std::cerr << "Unable to load menu background";

            poroTextures.insert(std::make_pair(i, poroTexture));
        }

        titleTextTexture.loadFromFile(MENU_TITLE_TEXT);
        titleText.setTexture(titleTextTexture);

        tbg.setPosition(0,0);
        titleText.setPosition(MENU_TITLE_TEXT_LEFT, MENU_TITLE_TEXT_TOP);

        MENU_PORO_IS_LOADED = true;
    }
    gameView.addView(ViewLayer::TITLESCREEN, this);
}

TitleScreen::~TitleScreen()
{
    //dtor
}

void TitleScreen::display()
{
    gameView.addDrawable(ViewLayer::MENU, &tbg);
    tbg.setTexture(*poroTextures[poroIndex]);
    gameView.addDrawable(ViewLayer::MENU, &titleText);

    // Animating title poro
    poroIndex++;
    if(poroIndex > MENU_BACKGROUND_LAST_FRAME)
    {
        poroIndex = MENU_BACKGROUND_FIRST_FRAME;
    }
}
