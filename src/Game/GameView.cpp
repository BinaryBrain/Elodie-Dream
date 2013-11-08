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

void GameView::draw(sf::Drawable* drawable) {
    window->clear(sf::Color(0x00, 0xFF, 0x00));
    window->draw(*drawable);
    window->display();
}
