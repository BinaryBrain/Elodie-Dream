#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <SFML/Graphics.hpp>

#include <iostream>

class GameView
{
    public:
        GameView();
        virtual ~GameView();

        void draw();
        void addDrawable(sf::Drawable*);

        sf::RenderWindow* getWindow();
    protected:
    private:
        sf::RenderWindow* window;
        std::vector<sf::Drawable*> toDraw;
};

#endif // GAMEVIEW_H
