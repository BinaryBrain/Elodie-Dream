#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <map>
#include <string>
#include "../const.h"
#include "../Level/Level.h"
#include "../Sprite/TileSprite.h"
#include "SFML/Graphics.hpp"

typedef std::map< LevelEnv, std::map< TileType, sf::Texture* > > TileTextures;

class TextureManager {
public:
    static TextureManager* getInstance();

    sf::Texture* getTileTexture(LevelEnv env, TileType type);
protected:
private:
    TextureManager();
    ~TextureManager();

    static TextureManager* textureManagerInstance;
    TextureManager& operator= (TextureManager const&); // Makes operator= private

    std::string getPath(LevelEnv env, TileType type);

    TileTextures textures;

    std::map<LevelEnv, string> LEVEL_ENV;

    std::map<TileType, std::string> TILE_TYPE;
};

#endif // TEXTUREMANAGER_H
