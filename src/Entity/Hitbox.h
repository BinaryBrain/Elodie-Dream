#ifndef HITBOX_H
#define HITBOX_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Hitbox
{
public:
    Hitbox(sf::FloatRect area);
    Hitbox(const Hitbox& original);
    virtual ~Hitbox();

    void move(sf::Vector2f* diff);
    void move(float dx, float dy);
    std::tuple<sf::Vector2f, sf::Vector2f> getPoints() const;
    sf::FloatRect getArea() const;
protected:
private:
    sf::FloatRect area;
};

#endif // HITBOX_H
