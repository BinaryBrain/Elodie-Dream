#include "GameView.h"

GameView::GameView() {
    window = new sf::RenderWindow(sf::VideoMode(1280, 720), "Elodie's Dream: Quest for Poros", sf::Style::Default);
}

GameView::~GameView() {
    delete window;
}

sf::RenderWindow* GameView::getWindow() {
    return window;
}

void GameView::addDrawable(ViewLayer viewKey, sf::Drawable* drawable) {
    drawableMap[viewKey].push_back(drawable);
}

void GameView::addView(ViewLayer viewKey, Displayable* disp) {
    viewMap[viewKey] = disp;
    drawableMap[viewKey] = std::vector<sf::Drawable*>();
    reset(viewKey);
}

void GameView::show(ViewLayer viewKey) {
    if(std::find(toDraw.begin(), toDraw.end(), viewKey) == toDraw.end()) {
        toDraw.push_back(viewKey);
    }
    viewMap[viewKey]->getView()->setSize(window->getDefaultView().getSize());
}

void GameView::hide(ViewLayer viewKey) {
    for(size_t i = 0; i < toDraw.size(); ++i) {
        if (toDraw[i] == viewKey) {
            toDraw.erase(toDraw.begin()+i);
        }
    }
}

void GameView::reset(ViewLayer viewKey) {
    centers[viewKey] = window->getDefaultView().getCenter();
}

void GameView::setCameraCenter(ViewLayer viewKey, const sf::Vector2f* pos) {
    setCameraCenter(viewKey, pos->x, pos->y);
}

void GameView::setCameraCenter(ViewLayer viewKey, float x, float y) {
    centers[viewKey].x = x;
    centers[viewKey].y = y;
}

void GameView::setFollowedPoint(ViewLayer viewKey, const sf::Vector2f* pos) {
    setFollowedPoint(viewKey, pos->x, pos->y);
}

void GameView::setFollowedPoint(ViewLayer viewKey, float x, float y) {
    sf::Vector2f viewSize = viewMap[viewKey]->getView()->getSize();

    float margin = viewSize.y/4;

    float camX = x+viewSize.x/2-viewSize.x/4; // 1/4 of the screen
    float camY;

    if(centers[viewKey].y-y > viewSize.y/2-margin) {
        camY = y+margin;
    } else if(y-centers[viewKey].y > viewSize.y/2-margin) {
        camY = y-margin;
    }

    setCameraCenter(viewKey, camX, camY);
}

void GameView::draw() {

    window->clear(sf::Color(0x00, 0x00, 0xFF, 0x00));

    sf::View view;

    for(size_t i = 0; i < toDraw.size(); ++i) {
        ViewLayer viewKey = toDraw[i];
        Displayable* disp = viewMap[viewKey];
        disp->getView()->setCenter(centers[viewKey]);
        disp->display(this);
        window->setView(*(disp->getView()));
        for(std::vector<sf::Drawable*>::iterator drawableIt = drawableMap[viewKey].begin(); drawableIt != drawableMap[viewKey].end(); ++drawableIt) {
            sf::Drawable* drawable = *drawableIt;
            window->draw(*drawable);
        }
    }

    window->display();

    for(std::vector<ViewLayer>::iterator keyIt = toDraw.begin(); keyIt != toDraw.end(); ++keyIt) {
        drawableMap[*keyIt].clear();
    }
}
