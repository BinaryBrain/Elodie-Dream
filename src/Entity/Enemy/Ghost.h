#ifndef GHOST_H_INCLUDED
#define GHOST_H_INCLUDED

#include "../../const.h"
#include "../Entity.h"
#include "../../Sprite/EntitySprite.h"
#include "../../Include/Collide.h"
#include "../../Include/EntityInfo.h"
#include "../../EventHandler/EventHandler.h"
#include "../../EntityManager/EntityManager.h"
#include "../Elodie.h"
#include "../../Sound/SoundManager.h"

class SoundManager;

enum class GhostState { STANDING };

class Ghost : public Entity {
public:
    Ghost();
    Ghost(sf::Vector2f position);
    Ghost(float x, float y);
    virtual ~Ghost();

    void update(sf::Time deltaTime);

    EntitySprite* getSprite();
    Hitbox returnCurrentHitbox();
    void doAttack(std::map< std::string, Entity* >& entities);
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
    int limitSpeed = GHOST_LIMIT_Y;
    int step = GHOST_STEP;

    GhostState state;

    std::map< GhostState, std::string > ANIMATIONS;
};

#endif // GHOST_H_INCLUDED
