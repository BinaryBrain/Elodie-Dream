#ifndef MAGMACUBE_H_INCLUDED
#define MAGMACUBE_H_INCLUDED

#include "../../const.h"
#include "../Entity.h"
#include "../../Sprite/EntitySprite.h"
#include "../../Include/Collide.h"
#include "../../Include/EntityInfo.h"
#include "../../EventHandler/EventHandler.h"
#include "../../EntityManager/EntityManager.h"
#include "../Elodie.h"

enum class MagmaCubeState { STANDING };

class MagmaCube : public Entity {
public:
    MagmaCube();
    MagmaCube(sf::Vector2f position);
    MagmaCube(float x, float y);
    virtual ~MagmaCube();

    void update(sf::Time deltaTime);

    EntitySprite* getSprite();
    Hitbox returnCurrentHitbox();
    void doAttack(std::map< std::string, Entity* >& entities);
    void takeDamage(int damage, bool ignore);
    void jump();
    void doStuff(EventHandler* const& event, std::vector< std::vector<TileSprite*> > const& tiles, std::map< std::string, Entity* >& entities, sf::Time animate);
    void pause();
    void play();
protected:

private:
    void init(float x, float y);
    int damage = 0;
    int jumpCD = 0;

    EntitySprite* sprite;

    MagmaCubeState state;

    std::map< MagmaCubeState, std::string > ANIMATIONS;
};

#endif // MAGMACUBE_H_INCLUDED
