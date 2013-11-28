#ifndef HITBOX_H
#define HITBOX_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Hitbox {
public:
    Hitbox(sf::Vector2f topLeft, sf::Vector2f bottomRight);
    Hitbox(const Hitbox& original);
    virtual ~Hitbox();

    void move(sf::Vector2f* diff);
    void move(float dx, float dy);
    std::tuple<sf::Vector2f, sf::Vector2f> getPoints() const;
protected:
private:
    sf::Vector2f topLeft;
    sf::Vector2f bottomRight;
};

#endif // HITBOX_H
