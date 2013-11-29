#include "TextureManager.h"

TextureManager* TextureManager::textureManagerInstance = NULL;

TextureManager::TextureManager() {
    TileTextures textures = TileTextures();

    /*
    LEVEL_ENV[LevelEnv::FIELD] = LEVELENV_FIELD;
    LEVEL_ENV[LevelEnv::UNIL] = LEVELENV_UNIL;
    LEVEL_ENV[LevelEnv::CASTLE] = LEVELENV_CASTLE;
    LEVEL_ENV[LevelEnv::VOLCANO] = LEVELENV_VOLCANO;
    LEVEL_ENV[LevelEnv::FREJLORD] = LEVELENV_FREJLORD;

    TILE_TYPE = {
        { TileType::GROUND, TILETYPE_GROUND },
        { TileType::ROCK, TILETYPE_ROCK },
        { TileType::ICE, TILETYPE_ICE }
    };*/
}

TextureManager::~TextureManager() {

}

TextureManager* TextureManager::getInstance() {
    if(!textureManagerInstance) textureManagerInstance = new TextureManager;
    return textureManagerInstance;
}

sf::Texture* TextureManager::getTileTexture(LevelEnv env, TileType type) {
    if(!textures[env][type]) {
        sf::Texture* tex = new sf::Texture();
        if(!tex->loadFromFile(getPath(env, type))) {
            // TODO handle error
        } else {
            textures[env][type] = tex;
        }
    }

    return textures[env][type];
}

std::string TextureManager::getPath(LevelEnv env, TileType type) {
    return TILES_TEXTURES_PATH+"/"+LEVELENV_FIELD+"/"+TILETYPE_ROCK+".png";
    //return TILES_TEXTURES_PATH+"/"+LEVEL_ENV[env]+"/"+TILE_TYPE[type]+".png";
}
