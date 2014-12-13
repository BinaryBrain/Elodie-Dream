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

class Entity;

typedef std::vector< std::vector<TileSprite*> > TileMap;
typedef std::map<std::string, Entity*> EntityMap;

enum class GameState
{
    INLEVEL = 0, INOVERWORLD, INMENU, INCONSOLE, PAUSE, SAVE, LOAD, EXIT, DEAD, NEWGAME, ENDINGSCREEN, INSCORE, INSTATS, OWFADEOUT, OWFADEIN
};

enum class LevelEnv
{
    FIELD = 0, CASTLE = 1, VOLCANO = 2, FRELJORD = 3, SPACE = 4, UNIL = 1000
};

enum class SoundType
{
    PUNCH, SPIKES, SHEEP, FOOTSTEP_GRASS, FOOTSTEP_GROUND, GHOST, MAGMACUBE, BRISTLE, BOTTLE, WOOSH
};

enum class EnemyType
{
    SHEEP, MAGMACUBE, BRISTLE, SPIKES, GHOST, CROW, REDLIGHT, METEORITE, ALIEN, LASER
};

#endif // ENV_H
