#ifndef BRISTLE_H_INCLUDED
#define BRISTLE_H_INCLUDED

#include "../Entity.h"
#include "../../Sprite/EntitySprite.h"
#include "../../Include/Collide.h"
#include "../../Include/EntityInfo.h"
#include "../../EventHandler/EventHandler.h"
#include "../../EntityManager/EntityManager.h"
#include "../Elodie.h"

class Bristle : public Entity
{
public:
    static const int DAMAGE;
    static const int SPEED_X;
    static const int SPEED_Y;
    static const int DETECTION;
    static const std::map< int, std::string > ANIMATIONS;

    enum State
    {
        STANDING,
        GRATTING
    };

public:
    Bristle();
    Bristle(sf::Vector2f position);
    Bristle(float x, float y);
    virtual ~Bristle();

    void doAttack(std::map< std::string, Entity* >& entities);
    void checkArea(std::map< std::string, Entity* >& entities);

    virtual void takeDamage(int damage, bool ignore);
    virtual void doStuff(const EventHandler& event, const std::vector< std::vector<TileSprite*> >& tiles,
                         std::map< std::string, Entity* >& entities, sf::Time animate);

private:
    bool charge = false;
};

#endif // BRISTLE_H_INCLUDED
