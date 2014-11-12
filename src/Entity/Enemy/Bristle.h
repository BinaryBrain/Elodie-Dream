#ifndef BRISTLE_H_INCLUDED
#define BRISTLE_H_INCLUDED

#include "../Entity.h"
#include "../../Sprite/EntitySprite.h"
#include "../../Include/Collide.h"
#include "../../Include/EntityInfo.h"
#include "../../EventHandler/EventHandler.h"
#include "../../EntityManager/EntityManager.h"
#include "../Elodie.h"

enum class BristleState { STANDING, GRATTING };

class Bristle : public Entity {
public:
    static const int DAMAGE;
    static const int SPEED_X;
    static const int SPEED_Y;
    static const int DETECTION;

    Bristle();
    Bristle(sf::Vector2f position);
    Bristle(float x, float y);
    virtual ~Bristle();

    void update(sf::Time deltaTime);

    EntitySprite* getSprite();
    Hitbox returnCurrentHitbox();
    void doAttack(std::map< std::string, Entity* >& entities);
    void checkArea(std::map< std::string, Entity* >& entities);
    void takeDamage(int damage, bool ignore);
    void doStuff(EventHandler* const& event, std::vector< std::vector<TileSprite*> > const& tiles, std::map< std::string, Entity* >& entities, sf::Time animate);
    void pause();
    void play();

private:
    void init(float x, float y);

    EntitySprite* sprite;

    BristleState state;
    bool charge = false;

    std::map< BristleState, std::string > ANIMATIONS;
};

#endif // BRISTLE_H_INCLUDED
