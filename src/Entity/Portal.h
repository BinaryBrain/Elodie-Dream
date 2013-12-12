#ifndef Portal_H_INCLUDED
#define Portal_H_INCLUDED

#include "../const.h"
#include "Entity.h"
#include "../Sprite/EntitySprite.h"
#include "../Include/Collide.h"
#include "../Include/EntityInfo.h"
#include "../EventHandler/EventHandler.h"
#include "../EntityManager/EntityManager.h"
#include "Elodie.h"
#include "../Sound/SoundManager.h"

class SoundManager;

enum class PortalState { STANDING };

class Portal : public Entity {
public:
    Portal();
    Portal(sf::Vector2f position);
    Portal(float x, float y);
    virtual ~Portal();

    void update(sf::Time deltaTime);

    EntitySprite* getSprite();
    Hitbox returnCurrentHitbox();
    void takeDamage(int damage, bool ignore);
    void doStuff(EventHandler* const& event, std::vector< std::vector<TileSprite*> > const& tiles, std::map< std::string, Entity* >& entities, sf::Time animate);
    void pause();
    void play();
protected:

private:
    void init(float x, float y);
    int damage = 0;
    SoundManager* soundManager;

    EntitySprite* sprite;

    PortalState state;

    std::map< PortalState, std::string > ANIMATIONS;
};

#endif // Portal_H_INCLUDED
