#include "GameView.h"

GameView::GameView()
{
    this->window = new sf::RenderWindow(sf::VideoMode(1280, 720), "Elodie's Dream: Quest for Poros", sf::Style::Default);
}

GameView::~GameView()
{
    delete window;
}

sf::RenderWindow* GameView::getWindow() {
    return window;
}

void GameView::addDrawable(sf::Drawable* drawable) {
    toDraw.push_back(drawable);
}

void GameView::draw() {
    sf::View view = window->getView();
    view.move(0, 0);
    window->setView(view);

    window->clear(sf::Color(0x00, 0xFF, 0x00));

    for(std::vector<sf::Drawable*>::iterator it = toDraw.begin(); it != toDraw.end(); ++it) {
        sf::Drawable* drawable = *it;
        window->draw(*drawable);
    }

    window->display();

    toDraw.clear();
}
