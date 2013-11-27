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

void GameView::addDrawable(sf::Drawable* drawable) {
    toDraw.push_back(drawable);
}

void GameView::reset() {
    window->setView(window->getDefaultView());
}

void GameView::setCameraCenter(const sf::Vector2f* pos) {
    sf::View view = window->getView();
    view.setCenter(*pos);
    window->setView(view);
}

void GameView::setCameraCenter(float x, float y) {
    sf::View view = window->getView();
    view.setCenter(x, y);
    window->setView(view);
}

void GameView::draw() {
    window->clear(sf::Color(0x00, 0x00, 0xFF));

    for(std::vector<sf::Drawable*>::iterator it = toDraw.begin(); it != toDraw.end(); ++it) {
        sf::Drawable* drawable = *it;
        window->draw(*drawable);
    }

    window->display();

    toDraw.clear();
}
