#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <SFML/Graphics.hpp>

#include <iostream>
#include <map>

#include "../Displayable/Displayable.h"

enum class ViewLayer {
    MENU, OVERWORLD, LEVEL, HUD
};

class GameView {
public:
    GameView();
    virtual ~GameView();

    void draw();
    void addDrawable(ViewLayer viewKey, sf::Drawable*);

    sf::RenderWindow* getWindow();

    void addView(ViewLayer viewKey, Displayable* disp);

    void hide(ViewLayer viewKey);
    void show(ViewLayer viewKey);

    void reset(ViewLayer viewKey);
    void setCameraCenter(ViewLayer viewKey, const sf::Vector2f* pos);
    void setCameraCenter(ViewLayer viewKey, float x, float y);
    void setFollowedPoint(ViewLayer viewKey, const sf::Vector2f* pos);
    void setFollowedPoint(ViewLayer viewKey, float x, float y);
protected:
private:
    std::map<ViewLayer, Displayable*> viewMap;
    std::map<ViewLayer, std::vector<sf::Drawable*>> drawableMap;
    std::vector<ViewLayer> toDraw;

    sf::RenderWindow* window;
    sf::Vector2f center;
};

#endif // GAMEVIEW_H
