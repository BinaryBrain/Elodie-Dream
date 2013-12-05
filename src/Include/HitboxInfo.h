#ifndef HITBOXINFO_H_INCLUDED
#define HITBOXINFO_H_INCLUDED

#include <vector>
#include <tuple>
#include "SFML/Graphics.hpp"

class HitboxInfo {
public:
    int row;
    std::vector< std::tuple< sf::Vector2f, sf::Vector2f > > hitboxes;
};

#endif // HITBOXINFO_H_INCLUDED
