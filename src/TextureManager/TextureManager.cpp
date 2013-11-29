#include "TextureManager.h"

TextureManager::TextureManager() {
    std::cout << LEVELENV_FIELD << std::endl;

    LEVEL_ENV = {
        {LevelEnv::FIELD, LEVELENV_FIELD},
        {LevelEnv::UNIL, LEVELENV_UNIL},
        {LevelEnv::CASTLE, LEVELENV_CASTLE},
        {LevelEnv::VOLCANO, LEVELENV_VOLCANO},
        {LevelEnv::FREJLORD, LEVELENV_FREJLORD}
    };

    std::cout << "TexMan: " << LEVEL_ENV[LevelEnv::UNIL] << std::endl;

    TILE_TYPE = {
        { TileType::GROUND, TILETYPE_GROUND },
        { TileType::ROCK, TILETYPE_ROCK },
        { TileType::ICE, TILETYPE_ICE }
    };
}

TextureManager::~TextureManager() {

}

sf::Texture* TextureManager::getTileTexture(LevelEnv env, TileType type) {
    if(!textures[env][type]) { // FIXME SEGFAULT
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
