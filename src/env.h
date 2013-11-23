#include <string>
#include <vector>
#include <map>
#include <iostream>

#include "Sprite/TileSprite.h"
#include "Entity/Entity.h"

typedef std::vector< std::vector<TileSprite*> > TileMap;
typedef std::map<std::string, Entity*> EntityMap;

enum class GameState {
    INLEVEL, INOVERWORLD, INMENU, EXIT
};
