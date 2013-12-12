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
    INLEVEL = 0, INOVERWORLD, INMENU, INCONSOLE, PAUSE, SAVE, LOAD, EXIT, DEAD
};

enum class LevelEnv {
    FIELD, UNIL, CASTLE, VOLCANO, FREJLORD
};

enum class SoundType {
    PUNCH, SPIKES, SHEEP, FOOTSTEP_GRASS, FOOTSTEP_GROUND, GHOST
};

#endif // ENV_H
