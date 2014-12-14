#include "GameView.h"

GameView::GameView()
{
    if(FULLSCREEN)
    {
        window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Elodie's Dream: Quest for Poros", sf::Style::Fullscreen);
    }
    else
    {
        window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Elodie's Dream: Quest for Poros", sf::Style::Default);
    }
}

GameView::~GameView()
{
    delete window;
}

sf::RenderWindow& GameView::getWindow()
{
    return *window;
}

float GameView::getSizeX()
{
    return window->getSize().x;
}

float GameView::getSizeY()
{
    return window->getSize().y;
}

void GameView::addDrawable(ViewLayer viewKey, sf::Drawable* drawable)
{
    drawableMap[viewKey].push_back(drawable);
}

void GameView::addView(ViewLayer viewKey, Displayable* disp)
{
    viewMap[viewKey] = disp;
    reset(viewKey);
}

void GameView::show(ViewLayer viewKey)
{
    if(std::find(toDraw.begin(), toDraw.end(), viewKey) == toDraw.end())
    {
        toDraw.push_back(viewKey);
    }
    if (zooms[viewKey]<=0)
    {
        viewMap[viewKey]->getView().setSize(window->getDefaultView().getSize()/zooms[viewKey]);
    }
}

void GameView::hide(ViewLayer viewKey)
{
    for(size_t i = 0; i < toDraw.size(); ++i)
    {
        if (toDraw[i] == viewKey)
        {
            toDraw.erase(toDraw.begin()+i);
        }
    }
}

void GameView::reset(ViewLayer viewKey)
{
    centers[viewKey] = window->getDefaultView().getCenter();
    setZoom(viewKey, 1);
}

void GameView::setCameraCenter(ViewLayer viewKey, const sf::Vector2f pos)
{
    setCameraCenter(viewKey, pos.x, pos.y);
}

void GameView::setCameraCenter(ViewLayer viewKey, float x, float y)
{
    centers[viewKey].x = x;
    centers[viewKey].y = y;
}

void GameView::followPoint(ViewLayer viewKey, const sf::Vector2f pos)
{
    followPoint(viewKey, pos.x, pos.y);
}

void GameView::followPoint(ViewLayer viewKey, float x, float y)
{
    sf::Vector2f viewSize = viewMap[viewKey]->getView().getSize();

    float marginTop = viewSize.y/7.9;
    float marginBot = viewSize.y/1.85;
    // margin = 0; // FIXME I bug with the zoom

    float camX = x+viewSize.x/2-viewSize.x/5; // 1/5 of the screen
    float camY = viewMap[viewKey]->getView().getCenter().y;

    if(centers[viewKey].y-y > viewSize.y/2-marginTop)
    {
        camY = y+(viewSize.y/2-marginTop);
    }
    else if(-centers[viewKey].y+y > viewSize.y/2-marginBot)
    {
        camY = y-(viewSize.y/2-marginBot);
    }

    setCameraCenter(viewKey, camX, camY);
}

void GameView::setZoom(ViewLayer viewKey, float zoom)
{
    zooms[viewKey] = zoom;
    viewMap[viewKey]->getView().setSize(window->getDefaultView().getSize()/zooms[viewKey]);
}

void GameView::draw()
{
    window->clear(sf::Color(0x00, 0x00, 0xFF, 0x00));

    sf::View view;

    for(size_t i = 0; i < toDraw.size(); ++i)
    {
        ViewLayer viewKey = toDraw[i];
        Displayable* disp = viewMap[viewKey];
        disp->getView().setCenter(centers[viewKey]);
        disp->display();
        disp->getView().setSize(window->getDefaultView().getSize()/zooms[viewKey]);
        window->setView(disp->getView());
        for(std::vector<sf::Drawable*>::iterator drawableIt = drawableMap[viewKey].begin(); drawableIt != drawableMap[viewKey].end(); ++drawableIt)
        {
            sf::Drawable* drawable = *drawableIt;
            window->draw(*drawable);
        }
    }

    window->display();

    for(std::vector<ViewLayer>::iterator keyIt = toDraw.begin(); keyIt != toDraw.end(); ++keyIt)
    {
        drawableMap[*keyIt].clear();
    }
}

bool GameView::isPointOutsideView(ViewLayer layer, sf::Vector2f point)
{
    return isPointOutsideView(layer, point.x, point.y);
}

bool GameView::isPointOutsideView(ViewLayer, float x, float y)
{
    float zoom = zooms[ViewLayer::LEVEL];

    sf::Vector2u windowSize = window->getSize();
    windowSize.x = windowSize.x/zoom;
    windowSize.y = windowSize.y/zoom;

    sf::Vector2f layerSize = viewMap[ViewLayer::LEVEL]->getView().getSize();
    layerSize.x /= 2;
    layerSize.y /= 2;

    float relX = x-(centers[ViewLayer::LEVEL].x-layerSize.x);
    float relY = y-(centers[ViewLayer::LEVEL].y-layerSize.y);

    return (relX < - CAMERA_TOL || relY < - CAMERA_TOL || relX > windowSize.x + CAMERA_TOL || relY > windowSize.y + CAMERA_TOL);
}
