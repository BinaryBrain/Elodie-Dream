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

void GameView::addDrawable(sf::Drawable* drawable) {
    toDraw.push_back(drawable);
}

void GameView::reset() {
    center = window->getView().getCenter();
}

void GameView::setCameraCenter(const sf::Vector2f* pos) {
    setCameraCenter(pos->x, pos->y);
}

void GameView::setCameraCenter(float x, float y) {
    this->center.x = x;
    this->center.y = y;
}

void GameView::setFollowedPoint(const sf::Vector2f* pos) {
    setFollowedPoint(pos->x, pos->y);
}

void GameView::setFollowedPoint(float x, float y) {
    sf::Vector2f viewSize = window->getView().getSize();

    float margin = viewSize.y/4;

    float camX = x+viewSize.x/2-viewSize.x/4; // 1/4 of the screen
    float camY;

    if(center.y-y > viewSize.y/2-margin) {
        camY = y+margin;
    }
    else if(y-center.y > viewSize.y/2-margin) {
        camY = y-margin;
    }

    setCameraCenter(camX, camY);
}

void GameView::draw() {
    sf::View view = window->getView();
    view.setCenter(center);
    window->setView(view);

    window->clear(sf::Color(0x00, 0x00, 0xFF));

    for(std::vector<sf::Drawable*>::iterator it = toDraw.begin(); it != toDraw.end(); ++it) {
        sf::Drawable* drawable = *it;
        window->draw(*drawable);
    }

    window->display();

    toDraw.clear();
}
