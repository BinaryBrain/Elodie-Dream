#include "Hitbox.h"

Hitbox::Hitbox(sf::FloatRect area)
{
    this->area = sf::FloatRect(area);
}

Hitbox::Hitbox(const Hitbox& original)
{
    this->area = original.getArea();
}

Hitbox::~Hitbox()
{

}

void Hitbox::move(sf::Vector2f* diff)
{
    this->area.left += diff->x;
    this->area.top += diff->y;
}

void Hitbox::move(float dx, float dy)
{
    sf::Vector2f dist(dx, dy);
    move(&dist);
}

std::tuple< sf::Vector2f, sf::Vector2f > Hitbox::getPoints() const
{
    return std::tuple< sf::Vector2f, sf::Vector2f >({area.left, area.top}, {area.left + area.width, area.top + area.height});
}

sf::FloatRect Hitbox::getArea() const
{
    return area;
}
