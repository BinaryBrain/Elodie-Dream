#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <SFML/Graphics.hpp>

#include <iostream>

class GameView {
public:
    GameView();
    virtual ~GameView();

    void draw();
    void addDrawable(sf::Drawable*);

    sf::RenderWindow* getWindow();

    void reset();
    void setCameraCenter(const sf::Vector2f* pos);
    void setCameraCenter(float x, float y);
    void setFollowedPoint(const sf::Vector2f* pos);
    void setFollowedPoint(float x, float y);
protected:
private:
    sf::RenderWindow* window;
    std::vector<sf::Drawable*> toDraw;
    sf::Vector2f center;
};

#endif // GAMEVIEW_H
