#include "Entity.h"

const int Entity::DAMAGE_CD = 25;

Entity::Entity(sf::Vector2f position, EntityType type, EntityName name,
               const std::string& spritePath, const std::string& spriteStance,
               const std::map< int, std::string >& anim, int stateArg,
               sf::Vector2f speedArg, int lifeArg, int damageArg) :
    speed(speedArg),
    life(lifeArg),
    damage(damageArg),
    state(stateArg),
    animations(anim)
{
    info = EntityManager::getInstance().getEnemyInfo(type, name);
    position.y -= (info->height - BLOCK_SIZE);

    sprite = new EntitySprite(info, ENTITIES_JSON_PATH + "/" + spritePath, spriteStance);
    dynamic_cast<EntitySprite*>(sprite)->changeStance(animations.at(state), sf::seconds(0.2f));
    sprite->setPosition(position);

    setHitboxes(info, sprite->getPosition());
}

//If this constructor is called, the class has to set info and sprite.
Entity::Entity(const std::map< int, std::string >& anim, int stateArg,
               sf::Vector2f speedArg, int lifeArg, int damageArg) :
    speed(speedArg),
    life(lifeArg),
    damage(damageArg),
    state(stateArg),
    animations(anim)
{
}

Entity::~Entity()
{
    delete sprite;
}

bool Entity::isInFront(sf::FloatRect entity, sf::FloatRect target, Direction dir)
{
    sf::FloatRect half;

    half.top = entity.top;
    half.width = entity.width / 2;
    half.height = entity.height;
    if (dir == Direction::LEFT)
    {
        half.left = entity.left;
    }
    else if (dir == Direction::RIGHT)
    {
        half.left = entity.left + half.width;
    }
    return half.intersects(target);
}

bool Entity::isAlive()
{
    return (life > 0);
}

void Entity::flipToLeft()
{
    sprite->setOrigin(sf::Vector2f(0,0));
    sprite->setScale(1, 1);
    direction = Direction::LEFT;
}

void Entity::flipToRight()
{
    sprite->setOrigin(sf::Vector2f(info->width,0));
    sprite->setScale(-1, 1);
    direction = Direction::RIGHT;
}

void Entity::changeStance(const std::string& stance, const sf::Time& speed)
{
    EntitySprite* cast;
    if (sprite && (cast = dynamic_cast<EntitySprite*>(sprite)))
    {
        cast->changeStance(stance, speed);
    }
}

void Entity::setDistance(Collide collisions)
{
    if (speed.x < 0)
    {
        speed.x = -collisions.left["distance"];
    }
    else if (speed.x > 0)
    {
        speed.x = collisions.right["distance"];
    }

    if (speed.y < 0)
    {
        speed.y = -collisions.top["distance"];
    }
    else
    {
        speed.y = collisions.bottom["distance"];
    }

    if(speed.x < 0)
    {
        flipToLeft();
    }
    else if (speed.x > 0)
    {
        flipToRight();
    }
}

void Entity::setHitboxes(EntityInfo *informations, const sf::Vector2f position)
{
    hitboxes.clear();
    for(std::map< std::string, HitboxInfo >::iterator it = informations->anim.begin();
            it != informations->anim.end(); ++it)
    {
        for(std::vector< sf::FloatRect >::iterator hitboxIt = it->second.hitboxes.begin();
                hitboxIt != it->second.hitboxes.end(); ++hitboxIt)
        {
            sf::FloatRect rec(*hitboxIt);
            rec.top += position.y;
            rec.left += position.x;
            hitboxes[it->first].push_back(Hitbox(rec));
        }
    }
}

void Entity::removeCurrentHitBox(std::string animation, int frame)
{
    hitboxes[animation].erase(hitboxes[animation].begin()+frame);
}

void Entity::addHitbox(std::string animation, Hitbox hitbox)
{
    hitboxes[animation].push_back(hitbox);
}

Hitbox Entity::getCurrentHitbox(std::string animation, int frame) const
{
    return Hitbox(hitboxes.at(animation).at(frame));
}

Hitbox Entity::returnCurrentHitbox() const
{
    if (sprite)
    {
        return (getCurrentHitbox(animations.at(state), sprite->getCurrentFrame()));
    }
    return (Hitbox(sf::FloatRect()));
}

//to update with new tiles
int Entity::checkTiles(const std::vector< std::vector<TileSprite*> >& world, int x, int y)
{
    TileType tile;

    if (x < 0 || x >= (int)world[0].size() || y < 0 || y >= (int)world.size())
    {
        return 0;
    }

    tile = (world[y][x] ? world[y][x]->getType() : TileType::VOID);

    if (tile != TileType::VOID) {
        return 1;
    }
    return 0;
}

sf::Sprite* Entity::getSprite() const
{
    return (sprite);
}

Collide Entity::collideWithTiles(const std::vector< std::vector<TileSprite*> >& world, float time)
{
    if (!sprite)
        return Collide();

    Hitbox hitbox = getCurrentHitbox(animations.at(state), sprite->getCurrentFrame());
    Collide collideWith;
    sf::Vector2f step(std::abs(speed.x), std::abs(speed.y));

    float minX = std::get<0>(hitbox.getPoints()).x;
    float maxX = std::get<1>(hitbox.getPoints()).x;
    float minY = std::get<0>(hitbox.getPoints()).y;
    float maxY = std::get<1>(hitbox.getPoints()).y;

    int mapPnt;
    int tot = 0, totMin = 0, totMax = 0, incMin = 0, incMax = 0;

    collideWith.ground = TileType::VOID;
    collideWith.left["distance"] = collideWith.right["distance"] = step.x;
    //The +-1 is here because the hitbox will touch a bit the bottom/top/left/right tile, but it should not disturb the adjacent face
    for(float y = minY + 1; round(y) != round((maxY - 1) + BLOCK_SIZE); y += BLOCK_SIZE)
    {
        if (y > (maxY - 1))
            y = (maxY - 1);

        mapPnt = (int)std::floor(y / BLOCK_SIZE);
        incMin = incMax = 0;
        for (float stepX = 0; stepX <= step.x + 1 / time; stepX += 1)
        {
            if (checkTiles(world, (int)std::floor((minX - stepX * time) / BLOCK_SIZE), mapPnt))
            {
                incMin = 1;
                if (collideWith.left["distance"] > stepX)
                    collideWith.left["distance"] = stepX;
            }
            if (checkTiles(world, (int)std::floor((maxX + stepX * time) / BLOCK_SIZE), mapPnt))
            {
                incMax = 1;
                if (collideWith.right["distance"] > stepX)
                    collideWith.right["distance"] = stepX;
            }
        }
        totMin += incMin;
        totMax += incMax;
        ++tot;
    }
    if (tot > 0)
    {
        collideWith.left["surface"] = (float)totMin / tot;
        collideWith.right["surface"] = (float)totMax / tot;
    }

    tot = totMin = totMax = 0;
    collideWith.top["distance"] = collideWith.bottom["distance"] = step.y;
    for(float x = minX + 1; std::round(x) != std::round((maxX - 1) + BLOCK_SIZE); x += BLOCK_SIZE)
    {
        if (x > (maxX - 1))
            x = (maxX - 1);

        mapPnt = (int)std::floor(x / BLOCK_SIZE);
        incMin = incMax = 0;
        for (float stepY = 0; stepY <= step.y + 1 / time; stepY += 1)
        {
            if (checkTiles(world, mapPnt, (int)std::floor((minY - stepY * time) / BLOCK_SIZE)))
            {
                incMin = 1;
                if (collideWith.top["distance"] > stepY)
                    collideWith.top["distance"] = stepY;
            }
            if (checkTiles(world, mapPnt, (int)std::floor((maxY + stepY * time) / BLOCK_SIZE)))
            {
                incMax = 1;
                if (collideWith.bottom["distance"] > stepY)
                    collideWith.bottom["distance"] = stepY;
            }
        }
        totMin += incMin;
        totMax += incMax;
        ++tot;
    }
    if (tot > 0)
    {
        collideWith.top["surface"] = (float)totMin / tot;
        collideWith.bottom["surface"] = (float)totMax / tot;
    }

    //On test les diagonales
    if (speed.x > 0 && speed.y > 0 && checkTiles(world, (int)std::floor((maxX - 2 + collideWith.right["distance"]*time) / BLOCK_SIZE), (int)std::floor((maxY - 2 + collideWith.bottom["distance"]*time) / BLOCK_SIZE)))
    {
        collideWith.right["surface"] = 0.1;
        while (checkTiles(world, (int)std::floor((maxX - 2 + collideWith.right["distance"]*time) / BLOCK_SIZE), (int)std::floor((maxY - 2 + collideWith.bottom["distance"]*time) / BLOCK_SIZE)))
            collideWith.right["distance"] -= 1;
    }
    if (speed.x < 0 && speed.y > 0 && checkTiles(world, (int)std::floor((minX + 1 - collideWith.left["distance"]*time) / BLOCK_SIZE), (int)std::floor((maxY - 2 + collideWith.bottom["distance"]*time) / BLOCK_SIZE)))
    {
        collideWith.left["surface"] = 0.1;
        while (checkTiles(world, (int)std::floor((minX + 1 - collideWith.left["distance"]*time) / BLOCK_SIZE), (int)std::floor((maxY - 2 + collideWith.bottom["distance"]*time) / BLOCK_SIZE)))
            collideWith.left["distance"] -= 1;
    }
    if (speed.x > 0 && speed.y < 0 && checkTiles(world, (int)std::floor((maxX - 2 + collideWith.right["distance"]*time) / BLOCK_SIZE), (int)std::floor((minY + 1 - collideWith.top["distance"]*time) / BLOCK_SIZE)))
    {
        collideWith.right["surface"] = 0.1;
        while (checkTiles(world, (int)std::floor((maxX - 2 + collideWith.right["distance"]*time) / BLOCK_SIZE), (int)std::floor((minY + 1 - collideWith.top["distance"]*time) / BLOCK_SIZE)))
            collideWith.right["distance"] -= 1;
    }
    if (speed.x < 0 && speed.y < 0 && checkTiles(world, (int)std::floor((minX + 1 - collideWith.left["distance"]*time) / BLOCK_SIZE), (int)std::floor((minY + 1 - collideWith.top["distance"]*time) / BLOCK_SIZE)))
    {
        collideWith.left["surface"] = 0.1;
        while (checkTiles(world, (int)std::floor((minX + 1 - collideWith.left["distance"]*time) / BLOCK_SIZE), (int)std::floor((minY + 1 - collideWith.top["distance"]*time) / BLOCK_SIZE)))
            collideWith.left["distance"] -= 1;
    }

    if (collideWith.left["distance"] < 0)
    {
        collideWith.left["distance"] = 0;
    }
    if (collideWith.right["distance"] < 0)
    {
        collideWith.right["distance"] = 0;
    }
    if (collideWith.top["distance"] < 0)
    {
        collideWith.top["distance"] = 0;
    }
    if (collideWith.bottom["distance"] < 0)
    {
        collideWith.bottom["distance"] = 0;
    }

    //On check le ground
    float x = minX + 1;
    float mapY = (int)std::floor((maxY + collideWith.bottom["distance"] * time) / BLOCK_SIZE + 0.5f);
    while(x < maxX - 1 && collideWith.ground == TileType::VOID && collideWith.bottom["surface"])
    {
        float mapX = (int)std::floor(x / BLOCK_SIZE);

        if (mapX >= 0 && mapX < (int)world[0].size() && mapY >= 0 && mapY < (int)world.size())
            collideWith.ground = world[mapY][mapX] ? world[mapY][mapX]->getType() : TileType::VOID;
        ++x;
    }

    return collideWith;
}

void Entity::computeGravity(sf::Time time)
{
    speed.y += gravity*time.asSeconds();
}

void Entity::move(sf::Vector2f& diff)
{
    move(diff.x, diff.y);
}

void Entity::move(float dx, float dy)
{
    if(sprite)
    {
        sprite->move(dx, dy);
    }

    for (std::map< std::string, std::vector< Hitbox > >::iterator it = hitboxes.begin();
            it != hitboxes.end(); ++it)
    {
        for(std::vector< Hitbox >::iterator hitbox = it->second.begin();
                hitbox != it->second.end(); ++hitbox)
        {
            hitbox->move(dx, dy);
        }
    }
}

void Entity::update(sf::Time deltaTime)
{
    if (sprite)
    {
        sprite->update(deltaTime);
    }
}

void Entity::pause()
{
    if (sprite)
    {
        sprite->pause();
    }
}

void Entity::play()
{
    if (sprite)
    {
        sprite->play();
    }
}

void Entity::setGravity(int newGravity)
{
    gravity = newGravity > 0 ? newGravity : gravity;
}
