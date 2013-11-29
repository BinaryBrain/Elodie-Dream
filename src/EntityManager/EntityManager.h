#ifndef ENTITYMANAGER_H_INCLUDED
#define ENTITYMANAGER_H_INCLUDED

#include <map>
#include <string>
#include "../const.h"
#include "../Level/Level.h"
#include "../Sprite/TileSprite.h"
#include "SFML/Graphics.hpp"

typedef std::map< LevelEnv, std::map< TileType, sf::Texture* > > TileTextures;

class EntityManager {
public:
    static EntityManager* getInstance();

    sf::Texture* getTileTexture(LevelEnv env, TileType type);
protected:
private:
    EntityManager();
    ~EntityManager();

    static EntityManager* entityManagerInstance;
    EntityManager& operator= (EntityManager const&); // Makes operator= private

    std::string getPath(LevelEnv env, TileType type);

    TileTextures textures;

    std::map<LevelEnv, string> LEVEL_ENV;

    std::map<TileType, std::string> TILE_TYPE;
};


#endif // ENTITYMANAGER_H_INCLUDED
