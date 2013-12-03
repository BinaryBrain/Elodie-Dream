#include "Entity.h"

Entity::Entity() {
    sprite = NULL;
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

void Entity::removeCurrentHitBox() {
    hitboxes.erase(hitboxes.begin()+currentHitbox);
    currentHitbox = 0;
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
            tile == TileType::ROCK ||
            tile == TileType::ICE)
        return 1;
    return 0;
}

Collide Entity::collideWithTiles(std::vector< std::vector<TileSprite*> > const& world, sf::Vector2f *vit, float time) {
    Collide collideWith;
    sf::Vector2f step(std::abs(vit->x), std::abs(vit->y));

    Hitbox hitbox = getCurrentHitbox();

    float minX = std::get<0>(hitbox.getPoints()).x;
    float maxX = std::get<1>(hitbox.getPoints()).x;
    float minY = std::get<0>(hitbox.getPoints()).y;
    float maxY = std::get<1>(hitbox.getPoints()).y;

    int mapPnt;
    int totMin = 0, totMax = 0, incMin = 0, incMax = 0;

    collideWith.left["distance"] = collideWith.right["distance"] = step.x;
    //The +-1 is here because the hitbox will touch a bit the bottom/top/left/right tile, but it should not disturb the adjacent face
    for(float y = minY + 1; y < maxY - 1; ++y) {
        mapPnt = (int)std::floor(y / 32);
        incMin = incMax = 0;
        for (float stepX = 0; stepX <= step.x + 1 / time; stepX += 1) {
            if (checkTiles(world, (int)std::floor((minX - stepX * time) / 32), mapPnt)) {
                incMin = 1;
                if (collideWith.left["distance"] > stepX)
                    collideWith.left["distance"] = stepX;
            }
            if (checkTiles(world, (int)std::floor((maxX + stepX * time) / 32), mapPnt)) {
                incMax = 1;
                if (collideWith.right["distance"] > stepX)
                    collideWith.right["distance"] = stepX;
            }
        }
        totMin += incMin;
        totMax += incMax;
    }
    if (maxY - minY > 0) {
        collideWith.left["surface"] = totMin / (maxY - minY + 1);
        collideWith.right["surface"] = totMax / (maxY - minY + 1);
    }

    totMin = totMax = 0;
    collideWith.top["distance"] = collideWith.bottom["distance"] = step.y;
    for(float x = minX + 1; x < maxX - 1; ++x) {
        mapPnt = (int)std::floor(x / 32);
        incMin = incMax = 0;
        for (float stepY = 0; stepY <= step.y + 1 / time; stepY += 1) {
            if (checkTiles(world, mapPnt, (int)std::floor((minY - stepY * time) / 32))) {
                incMin = 1;
                if (collideWith.top["distance"] > stepY)
                    collideWith.top["distance"] = stepY;
            }
            if (checkTiles(world, mapPnt, (int)std::floor((maxY + stepY * time) / 32))) {
                incMax = 1;
                if (collideWith.bottom["distance"] > stepY)
                    collideWith.bottom["distance"] = stepY;
            }
        }
        totMin += incMin;
        totMax += incMax;
    }
    if (maxX - minX > 0) {
        collideWith.top["surface"] = totMin / (maxX - minX + 1);
        collideWith.bottom["surface"] = totMax / (maxX - minX + 1);
    }

    if (!collideWith.bottom["surface"] && !collideWith.right["surface"] && checkTiles(world, (int)std::floor((maxX + collideWith.right["distance"]*time) / 32), (int)std::floor((maxY + collideWith.bottom["distance"]*time) / 32))) {
        collideWith.right["surface"] = 0.1;
        while (checkTiles(world, (int)std::floor((maxX + collideWith.right["distance"]*time) / 32), (int)std::floor((maxY + collideWith.bottom["distance"]*time) / 32)))
            collideWith.right["distance"] -= 1;
    }
    if (!collideWith.bottom["surface"] && !collideWith.left["surface"] && checkTiles(world, (int)std::floor((minX - collideWith.left["distance"]*time) / 32), (int)std::floor((maxY + collideWith.bottom["distance"]*time) / 32))) {
        collideWith.left["surface"] = 0.1;
        while (checkTiles(world, (int)std::floor((minX - collideWith.left["distance"]*time) / 32), (int)std::floor((maxY + collideWith.bottom["distance"]*time) / 32)))
            collideWith.left["distance"] -= 1;
    }
    if (!collideWith.top["surface"] && !collideWith.right["surface"] && checkTiles(world, (int)std::floor((maxX + collideWith.right["distance"]*time) / 32), (int)std::floor((minY - collideWith.top["distance"]*time) / 32))) {
        collideWith.right["surface"] = 0.1;
        while (checkTiles(world, (int)std::floor((maxX + collideWith.right["distance"]*time) / 32), (int)std::floor((minY - collideWith.top["distance"]*time) / 32)))
            collideWith.right["distance"] -= 1;
    }
    if (!collideWith.top["surface"] && !collideWith.left["surface"] && checkTiles(world, (int)std::floor((minX - collideWith.left["distance"]*time) / 32), (int)std::floor((minY - collideWith.top["distance"]*time) / 32))) {
        collideWith.left["surface"] = 0.1;
        while (checkTiles(world, (int)std::floor((minX - collideWith.left["distance"]*time) / 32), (int)std::floor((minY - collideWith.top["distance"]*time) / 32)))
            collideWith.left["distance"] -= 1;
    }
    return collideWith;
}

void Entity::computeGravity(sf::Time time) {
    speed.y += 1000*time.asSeconds();
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
