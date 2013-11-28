#include "GameView.h"

GameView::GameView() {
    window = new sf::RenderWindow(sf::VideoMode(1280, 720), "Elodie's Dream: Quest for Poros", sf::Style::Default);
    center = window->getView().getCenter();
}

GameView::~GameView() {
    delete window;
}

sf::RenderWindow* GameView::getWindow() {
    return window;
}

void GameView::addDrawable(ViewLayer viewKey, sf::Drawable* drawable) {
    toDrawMap[viewKey].push_back(drawable);
}

void GameView::addView(ViewLayer viewKey, sf::View* view){
    viewMap[viewKey] = view;
}

void GameView::removeView(ViewLayer viewKey){
    for(std::vector<ViewLayer>::iterator it = toDraw.begin(); it != toDraw.end(); ++it) {
        if (*it == viewKey){
            toDraw.erase(it);
        }
    }
}

void GameView::reset() {
    center = window->getDefaultView().getCenter();
}

void GameView::setCameraCenter(ViewLayer viewKey, const sf::Vector2f* pos) {
    viewMap[viewKey]->setCenter(pos);
}

void GameView::setCameraCenter(ViewLayer viewKey, float x, float y) {
    setCameraCenter(viewKey, &sf::Vector2f(x,y))
}

void GameView::setFollowedPoint(ViewLayer viewKey, const sf::Vector2f* pos) {
    setFollowedPoint(viewKey, pos->x, pos->y);
}

void GameView::setFollowedPoint(ViewLayer viewKey, float x, float y) {
    sf::Vector2f viewSize = viewMap[viewKey]->getSize();

    float margin = viewSize.y/4;

    float camX = x+viewSize.x/2-viewSize.x/4; // 1/4 of the screen
    float camY;

    if(center.y-y > viewSize.y/2-margin) {
        camY = y+margin;
    }
    else if(y-center.y > viewSize.y/2-margin) {
        camY = y-margin;
    }

    setCameraCenter(viewKey, camX, camY);
}

void GameView::draw() {
    sf::View view = window->getView();
    window->setView(view);

    window->clear(sf::Color(0x00, 0x00, 0xFF));

    for(std::vector<sf::Drawable*>::iterator it = toDrawOnMain.begin(); it != toDrawOnMain.end(); ++it) {
        sf::Drawable* drawable = *it;
        window->draw(*drawable);
    }

    window->display();

    toDrawOnMain.clear();
}
