#ifndef ENTITYINFO_H_INCLUDED
#define ENTITYINFO_H_INCLUDED

#include <map>
#include <string>
#include "HitboxInfo.h"

class EntityInfo
{
public:
    int height;
    int width;

    std::map< std::string, HitboxInfo > anim;
};

#endif // ENTITYINFO_H_INCLUDED
