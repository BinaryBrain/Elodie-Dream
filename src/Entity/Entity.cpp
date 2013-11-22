#include "Entity.h"
#include "../Sprite/TileSprite.h"

Entity::Entity() {
    sprite = NULL;
}

Entity::~Entity() {
    if(sprite) {
        delete sprite;
    }
}

void Entity::setCurrentHitbox(int current) {
    currentHitbox = current;
}

void Entity::addHitbox(std::tuple< sf::Vector2f, sf::Vector2f > hitbox) {
    hitboxes.push_back(hitbox);
}

std::tuple< sf::Vector2f, sf::Vector2f > Entity::getCurrentHitbox() {
    return hitboxes[currentHitbox];
}

void Entity::updateHitboxes(sf::Vector2f speed) {
    for (unsigned int i(0); i < hitboxes.size(); ++i) {
        std::get<0>(hitboxes[i]) = std::get<0>(hitboxes[i]) + speed;
        std::get<1>(hitboxes[i]) = std::get<1>(hitboxes[i]) + speed;
    }
}

//to update with new tiles
int Entity::checkTiles(std::vector< std::vector<TileSprite*> > const& world, int x, int y) {
    TileType tile;

    if (x < 0 || x >= (int)world[0].size() || y < 0 || y >= (int)world.size())
        return 0;

    tile = world[y][x] ? world[y][x]->getType() : TileType::VOID;
    if (tile == TileType::GROUND ||
        tile == TileType::GRASS ||
        tile == TileType::STONE)
        return 1;
    return 0;
}

std::map< std::string, float > Entity::collideWithTiles(std::vector< std::vector<TileSprite*> > const& world) {
    std::map< std::string, float > collideWith = {{"up", 0}, {"right", 0}, {"down", 0}, {"left", 0}};

    std::tuple< sf::Vector2f, sf::Vector2f > hitbox = getCurrentHitbox();

    float minX(std::get<0>(hitbox).x), maxX(std::get<1>(hitbox).x), minY(std::get<0>(hitbox).y), maxY(std::get<1>(hitbox).y);
    int mapPnt;

    int totMin(0), totMax(0);

    for(float y = minY; y <= maxY; ++y)
    {
        mapPnt = (int)std::floor(y / 32);
        totMin += checkTiles(world, (int)std::floor((minX - 1) / 32), mapPnt);
        totMax += checkTiles(world, (int)std::floor((maxX + 1) / 32), mapPnt);
    }
    if (maxY - minY > 0) {
        collideWith["left"] = totMin / (maxY - minY + 1);
        collideWith["right"] = totMax / (maxY - minY + 1);
    }

    totMin = totMax = 0;
    for(float x = minX; x <= maxX; ++x)
    {
        mapPnt = (int)std::floor(x / 32);
        totMin += checkTiles(world, mapPnt, (int)std::floor((minY - 1) / 32));
        totMax += checkTiles(world, mapPnt, (int)std::floor((maxY + 1) / 32));
    }
    if (maxX - minX > 0) {
        collideWith["up"] = totMin / (maxX - minX + 1);
        collideWith["down"] = totMax / (maxX - minX + 1);
    }
    return collideWith;
}
