#include "Entity.h"
#include "../Sprite/TileSprite.h"

Entity::Entity() {
    sprite = NULL;
}

Entity::Entity(sf::Sprite* sprite) {
    this->sprite = sprite;
}

Entity::~Entity() {
    if(sprite) {
        delete sprite;
    }
}

void Entity::setEntitySprite(sf::Sprite* sprite) {
    this->sprite = sprite;
}

void Entity::setCurrentHitbox(int current) {
    currentHitbox = current;
}

void Entity::addHitbox(Hitbox hitbox) {
    hitboxes.push_back(hitbox);
}

Hitbox Entity::getCurrentHitbox() {
    return Hitbox(hitboxes[currentHitbox]);
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

    Hitbox hitbox = getCurrentHitbox();

    float minX(std::get<0>(hitbox.getPoints()).x);
    float maxX(std::get<1>(hitbox.getPoints()).x);
    float minY(std::get<0>(hitbox.getPoints()).y);
    float maxY(std::get<1>(hitbox.getPoints()).y);

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

void Entity::computeGravity() {

}

void Entity::move(sf::Vector2f& diff) {
    move(diff.x, diff.y);
}

void Entity::move(float dx, float dy) {
    if(sprite) {
        sprite->move(dx, dy);
    }

    for(std::vector<Hitbox>::iterator hitbox = hitboxes.begin(); hitbox != hitboxes.end(); hitbox++) {
        hitbox->move(dx, dy);
    }
}
