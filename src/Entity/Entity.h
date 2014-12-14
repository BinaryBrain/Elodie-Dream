#ifndef ENTITIE_H
#define ENTITIE_H

#include <iostream>
#include <map>
#include <SFML/Graphics.hpp>

#include "../Sprite/TileSprite.h"
#include "../Sprite/AnimatedSprite.h"
#include "../EventHandler/EventHandler.h"
#include "../Sprite/EntitySprite.h"
#include "../EntityManager/EntityManager.h"
#include "../Json/JsonAccessor.h"
#include "../Include/Collide.h"
#include "../Include/EntityInfo.h"
#include "../const.h"
#include "Hitbox.h"

/**
 * The class representing entities.
 */
class Entity
{
public:
    static const int DAMAGE_CD;

    enum Direction
    {
        LEFT, RIGHT
    };

public:
    /**
     * \brief The constructor of Entity. Sets its sprite to be NULL.
     */
    Entity(sf::Vector2f position, EntityType type, EntityName name,
           const std::string& spritePath, const std::string& spriteStance,
           const std::map< int, std::string >& animations, int stateArg,
           sf::Vector2f speedArg = {0, 0}, int lifeArg = 0, int damageArg = 0);

    Entity(const std::map< int, std::string >& anim, int stateArg,
           sf::Vector2f speedArg = {0, 0}, int lifeArg = 0, int damageArg = 0);
    /**
     * \brief The constructor of Entity. sprite needs to be allocated.
     */
    Entity();
    /**
     * \brief The destructor of Entity.
     */
    virtual ~Entity();

    void setHitboxes(EntityInfo *informations, const sf::Vector2f position);
    void addHitbox(std::string animation, Hitbox hitbox);
    void removeCurrentHitBox(std::string animation, int frame);
    Hitbox getCurrentHitbox(std::string animation, int frame) const;
    Hitbox returnCurrentHitbox() const;

    Collide collideWithTiles(const std::vector< std::vector<TileSprite*> >& world, float time);

    /**
     * \brief A getter to the main Sprite
     *
     * \return A pointer to the Sprite.
     */
    sf::Sprite* getSprite() const;

    bool isInFront(sf::FloatRect entity, sf::FloatRect target, Direction dir);
    bool isAlive();

    void flipToLeft();
    void flipToRight();
    void changeStance(const std::string& stance, const sf::Time& speed);
    void setDistance(Collide collisions);

    virtual void takeDamage(int damage, bool ignore) = 0;
    virtual void doStuff(const EventHandler& event, const std::vector< std::vector<TileSprite*> >& tiles,
                         std::map< std::string, Entity* >& entities, sf::Time animate) = 0;

    void computeGravity(sf::Time time);
    void move(sf::Vector2f& diff);
    void move(float dx, float dy);

    void update(sf::Time deltaTime);
    void pause();
    void play();
    void setGravity(int newGravity);

protected:
    AnimatedSprite* sprite;
    EntityInfo* info = NULL;
    Direction direction = Direction::LEFT;
    sf::Vector2f speed;

    int life;
    int damage;
    int damageCD = 0;
    int state;

    const std::map< int, std::string >& animations;

private:
    int checkTiles(std::vector< std::vector<TileSprite*> > const& world, int x, int y);
    std::map< std::string, std::vector< Hitbox > > hitboxes;
    int gravity = 1000;
};

#endif // ENTITIES_H
