#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <SFML/Graphics.hpp>

class GameView
{
    public:
        GameView();
        virtual ~GameView();

        void draw();
        void draw(sf::Drawable* drawable);

        sf::RenderWindow* getWindow();
    protected:
    private:
        sf::RenderWindow* window;
};

#endif // GAMEVIEW_H
