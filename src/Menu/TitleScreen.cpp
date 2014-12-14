#include "../Utils/Utils.h"
#include "TitleScreen.h"

const std::string TitleScreen::TITLE_TEXT = "assets/img/sprites/title/title.png";
const std::string TitleScreen::ANIMATED_BACKGROUND_PATH = "assets/img/sprites/title/poro";

TitleScreen::TitleScreen(GameView& gameView) : Displayable(gameView)
{
    // Background
    if(!MENU_PORO_IS_LOADED)
    {
        poroIndex = MENU_BACKGROUND_FIRST_FRAME;
        int lastFrame = MENU_BACKGROUND_LAST_FRAME;

        if(DEV_MODE) {
            lastFrame = MENU_BACKGROUND_FIRST_FRAME;
        }

        for(int i = MENU_BACKGROUND_FIRST_FRAME; i <= lastFrame; i++)
        {
            sf::Texture* poroTexture = new sf::Texture();
            if (!poroTexture->loadFromFile(ANIMATED_BACKGROUND_PATH+"/"+Utils::toStringWithLength(i, 4)+".png"))
            {
                std::cerr << "Unable to load menu background" << std::endl;
            }

            poroTextures.insert(std::make_pair(i, poroTexture));
        }

        titleTextTexture.loadFromFile(TITLE_TEXT);
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

    int lastFrame = MENU_BACKGROUND_LAST_FRAME;

    if(DEV_MODE) {
        lastFrame = MENU_BACKGROUND_FIRST_FRAME;
    }

    if(poroIndex > lastFrame)
    {
        poroIndex = MENU_BACKGROUND_FIRST_FRAME;
    }
}
