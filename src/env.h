#ifndef ENV_H
#define ENV_H

#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <iostream>
#include <utility>
#include <cmath>

#include "Sprite/TileSprite.h"
#include "Entity/Entity.h"

typedef std::vector< std::vector<TileSprite*> > TileMap;
typedef std::map<std::string, Entity*> EntityMap;

enum class GameState {
    INLEVEL, INOVERWORLD, INMENU, INCONSOLE, EXIT
};

enum class LevelEnv {
    FIELD, UNIL, CASTLE, VOLCANO, FREJLORD
};

#endif // ENV_H
