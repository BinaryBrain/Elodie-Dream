#include "TextureManager.h"

TextureManager::TextureManager() {
    LEVEL_ENV = {
        {LevelEnv::FIELD, LEVELENV_FIELD},
        {LevelEnv::UNIL, LEVELENV_UNIL},
        {LevelEnv::CASTLE, LEVELENV_CASTLE},
        {LevelEnv::VOLCANO, LEVELENV_VOLCANO},
        {LevelEnv::FREJLORD, LEVELENV_FREJLORD}
    };

    TILE_TYPE = {
        { TileType::GROUND, TILETYPE_GROUND },
        { TileType::ROCK, TILETYPE_ROCK },
        { TileType::ICE, TILETYPE_ICE }
    };
}

TextureManager::~TextureManager() {
    for(std::map< LevelEnv, std::map< TileType, sf::Texture* > >::iterator it = textures.begin(); it != textures.end(); ++it) {
        for(std::map< TileType, sf::Texture* >::iterator texture = it->second.begin(); texture != it->second.end(); ++texture) {
            sf::Texture* tex = texture->second;
            if(tex) {
                delete tex;
            }
        }
    }
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
    return TILES_TEXTURES_PATH+"/"+LEVEL_ENV[env]+"/"+TILE_TYPE[type]+".png";
}
