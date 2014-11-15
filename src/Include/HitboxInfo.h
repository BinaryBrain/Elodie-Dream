#ifndef HITBOXINFO_H_INCLUDED
#define HITBOXINFO_H_INCLUDED

#include <vector>
#include "SFML/Graphics.hpp"

class HitboxInfo
{
public:
    int row;
    std::vector< sf::FloatRect > hitboxes;
};

#endif // HITBOXINFO_H_INCLUDED
