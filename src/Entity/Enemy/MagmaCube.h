#ifndef MAGMACUBE_H_INCLUDED
#define MAGMACUBE_H_INCLUDED

#include "../Entity.h"
#include "../../Sprite/EntitySprite.h"
#include "../../Include/Collide.h"
#include "../../Include/EntityInfo.h"
#include "../../EventHandler/EventHandler.h"
#include "../../EntityManager/EntityManager.h"
#include "../Elodie.h"

class MagmaCube : public Entity
{
public:
    static const int DAMAGE;
    static const int JUMP_CD;
    static const int MOVE_X;
    static const int MOVE_Y;
    static const std::map< int, std::string > ANIMATIONS;

    enum State
    {
        STANDING
    };

public:
    MagmaCube();
    MagmaCube(sf::Vector2f position);
    MagmaCube(float x, float y);
    virtual ~MagmaCube();

    void doAttack(std::map< std::string, Entity* >& entities);
    void jump();

    virtual void takeDamage(int damage, bool ignore);
    virtual void doStuff(const EventHandler& event, const std::vector< std::vector<TileSprite*> >& tiles,
                         std::map< std::string, Entity* >& entities, sf::Time animate);

private:
    int jumpCD = 0;
};

#endif // MAGMACUBE_H_INCLUDED
