#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <SFML/Graphics.hpp>

#include <iostream>
#include <map>

#include "../const.h"
#include "../env.h"
#include "../Displayable/Displayable.h"

enum class ViewLayer
{
    MENU, OVERWORLD, LEVEL, HUD, CONSOLE, GIRLY, DEATH, SKY, EARTH, SCORE, STATS, ENDINGSCREEN, TITLESCREEN
};

class GameView
{
public:
    GameView();
    virtual ~GameView();

    void draw();
    void addDrawable(ViewLayer viewKey, sf::Drawable*);

    sf::RenderWindow& getWindow();
    float getSizeX();
    float getSizeY();

    void addView(ViewLayer viewKey, Displayable* disp);

    void hide(ViewLayer viewKey);
    void show(ViewLayer viewKey);

    void reset(ViewLayer viewKey);
    void setCameraCenter(ViewLayer viewKey, const sf::Vector2f pos);
    void setCameraCenter(ViewLayer viewKey, float x, float y);
    void followPoint(ViewLayer viewKey, const sf::Vector2f pos);
    void followPoint(ViewLayer viewKey, float x, float y);
    void setZoom(ViewLayer viewKey, float zoom);

    bool isPointOutsideView(ViewLayer layer, sf::Vector2f point);
    bool isPointOutsideView(ViewLayer layer, float x, float y);
protected:
private:
    std::map<ViewLayer, Displayable*> viewMap;
    std::map<ViewLayer, std::vector<sf::Drawable*>> drawableMap;
    std::vector<ViewLayer> toDraw;
    std::map<ViewLayer, sf::Vector2f> centers;
    std::map<ViewLayer, float> zooms;

    sf::RenderWindow* window;
};

#endif // GAMEVIEW_H
