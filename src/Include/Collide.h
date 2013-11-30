#ifndef COLLIDE_H_INCLUDED
#define COLLIDE_H_INCLUDED

class Collide {
public:
    std::map< std::string, float > top = {{"surface", 0}, {"distance", 0}};
    std::map< std::string, float > right = {{"surface", 0}, {"distance", 0}};
    std::map< std::string, float > bottom = {{"surface", 0}, {"distance", 0}};
    std::map< std::string, float > left = {{"surface", 0}, {"distance", 0}};
};

#endif // COLLIDE_H_INCLUDED
