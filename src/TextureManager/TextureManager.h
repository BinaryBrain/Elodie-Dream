#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include "SFML/Graphics.hpp"

#include <map>
#include <string>
#include "../const.h"
#include "../env.h"
#include "../Sprite/TileSprite.h"

typedef std::map< LevelEnv, std::map< TileType, sf::Texture* > > TileTextures;

class TextureManager
{
public:
    TextureManager();
    virtual ~TextureManager();

    sf::Texture* getTileTexture(LevelEnv env, TileType type);
protected:
private:
    std::string getPath(LevelEnv env, TileType type);

    TileTextures textures;

    std::map<LevelEnv, std::string> LEVEL_ENV;

    std::map<TileType, std::string> TILE_TYPE;
};

#endif // TEXTUREMANAGER_H
