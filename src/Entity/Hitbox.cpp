#include "Hitbox.h"

Hitbox::Hitbox(sf::Vector2f topLeft, sf::Vector2f bottomRight) {
    this->topLeft = sf::Vector2f(topLeft);
    this->bottomRight = sf::Vector2f(bottomRight);
}

Hitbox::Hitbox(const Hitbox& original) {
    this->topLeft = std::get<0>(original.getPoints());
    this->bottomRight = std::get<1>(original.getPoints());
}

Hitbox::~Hitbox() {

}

void Hitbox::move(sf::Vector2f* diff) {
    this->topLeft += *diff;
    this->bottomRight += *diff;
}

void Hitbox::move(float dx, float dy) {
    sf::Vector2f dist(dx, dy);
    move(&dist);
}

std::tuple< sf::Vector2f, sf::Vector2f > Hitbox::getPoints() const {
    return std::tuple< sf::Vector2f, sf::Vector2f >(topLeft, bottomRight);
}
