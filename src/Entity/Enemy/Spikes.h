#ifndef SPIKES_H_INCLUDED
#define SPIKES_H_INCLUDED

#include "../../const.h"
#include "../Entity.h"
#include "../../Sprite/EnemySprite/SpikesSprite.h"
#include "../../Include/Collide.h"
#include "../../Include/EntityInfo.h"
#include "../../EventHandler/EventHandler.h"
#include "../../EntityManager/EntityManager.h"
#include "../Elodie.h"

enum class SpikesState { WAITING, ACTIVATED, UNACTIVATED };

class Spikes : public Entity {
public:
    Spikes();
    Spikes(sf::Vector2f position);
    Spikes(float x, float y);
    virtual ~Spikes();

    void update(sf::Time deltaTime);

    SpikesSprite* getSprite();
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
    bool activated = false;

    SpikesSprite* sprite;

    SpikesState state;

    std::map< SpikesState, std::string > ANIMATIONS;
};

#endif // SPIKES_H_INCLUDED
